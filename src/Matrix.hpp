/**
 * @file Matrix.hpp
 * @brief This file contains the declaration of the Matrix class.
 */

#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include "Comm.hpp"
#include "Vector.hpp"
#include "matvec.hpp"
#include "shared.hpp"

/**
 * @class Matrix
 * @brief Represents a matrix and provides matrix operations.
 */
class Matrix {

private:
    Comm& comm; /**< Reference to the communication object. */
    Complex* mat_freq_tosi; /**< Pointer to the matrix frequency in TOSI format. */
    Complex* mat_freq_tosi_other
        = nullptr; /**< Pointer to the other matrix frequency in TOSI format. */
    unsigned int padded_size; /**< The padded block size of the matrix. */
    unsigned int block_size; /**< The unpadded block size of the matrix. */
    unsigned int num_cols; /**< The number of columns in the matrix. */
    unsigned int num_rows; /**< The number of rows in the matrix. */
    unsigned int glob_num_cols; /**< The global number of columns in the matrix. */
    unsigned int glob_num_rows; /**< The global number of rows in the matrix. */
    double* col_vec_unpad; /**< Pointer to the unpadded column vector. */
    double* col_vec_pad; /**< Pointer to the padded column vector. */
    double* row_vec_pad; /**< Pointer to the padded row vector. */
    double* row_vec_unpad; /**< Pointer to the unpadded row vector. */
    double* res_pad; /**< Pointer to the padded result vector. */
    Complex* col_vec_freq; /**< Pointer to the column vector frequency. */
    Complex* row_vec_freq; /**< Pointer to the row vector frequency. */
    Complex* col_vec_freq_tosi; /**< Pointer to the column vector frequency in TOSI format. */
    Complex* row_vec_freq_tosi; /**< Pointer to the row vector frequency in TOSI format. */
    cufftHandle forward_plan; /**< The forward plan for FFT. */
    cufftHandle inverse_plan; /**< The inverse plan for FFT. */
    cufftHandle forward_plan_conj; /**< The forward plan for conjugate FFT. */
    cufftHandle inverse_plan_conj; /**< The inverse plan for conjugate FFT. */
    bool initialized = false; /**< Flag indicating if the matrix is initialized. */
    bool has_mat_freq_tosi_other
        = false; /**< Flag indicating if the other matrix frequency in TOSI format exists. */

    /*
     * @brief Initializes the matrix (usued by the constructors).
     * @param cols The number of columns in the matrix (local or global based on value of global_sizes).
     * @param rows The number of rows in the matrix (local or global based on value of global_sizes).
     * @param block_size The block size of the matrix without padding.
     * @param global_sizes Flag indicating whether the sizes are global.
     */
    void initialize(
        unsigned int cols, unsigned int rows, unsigned int block_size, bool global_sizes);

public:
    /**
     * @brief Constructs a Matrix object.
     * @param comm The communication object (passed as reference).
     * @param cols The number of columns in the matrix (local or global based on value of global_sizes).
     * @param rows The number of rows in the matrix (local or global based on value of global_sizes).
     * @param block_size The block size of the matrix without padding.
     * @param global_sizes Flag indicating whether the sizes are global.
     */
    Matrix(Comm& comm, unsigned int cols, unsigned int rows, unsigned int block_size,
        bool global_sizes = false);

    /**
     * @brief Constructs a Matrix object from a meta file.
     * @param comm The communication object (passed as reference).
     * @param path Path to the directory containing the matrix data.
     *
     */
    Matrix(Comm& comm, std::string path);

    /**
     * @brief Destroys the Matrix object. Frees the memory allocated for the matrix data.
     */
    ~Matrix();

    /**
     * @brief Initializes the matrix from a file.
     * @param dirname The path to the directory containing the adjoint vectors.
     */
    void init_mat_from_file(std::string dirname);

    /**
     * @brief Initializes the matrix with ones.
     */
    void init_mat_ones();

    /**
     * @brief Performs matrix-vector multiplication.
     * @param x The input vector.
     * @param y The output vector.
     * @param full Flag indicating if the matvec is with the full matrix F*F or just F.
     */
    void matvec(Vector& x, Vector& y, bool full = false);

    /**
     * @brief Performs conjugate transpose matrix-vector multiplication.
     * @param x The input vector.
     * @param y The output vector.
     * @param full Flag indicating if the matvec is with the full matrix FF* or just F*.
     */
    void transpose_matvec(Vector& x, Vector& y, bool full = false);

    // Getters
    double* get_col_vec_unpad()
    {
        return col_vec_unpad;
    } /**< Returns the unpadded column vector. */
    double* get_col_vec_pad() { return col_vec_pad; } /**< Returns the padded column vector. */
    double* get_row_vec_pad() { return row_vec_pad; } /**< Returns the padded row vector. */
    double* get_row_vec_unpad() { return row_vec_unpad; } /**< Returns the unpadded row vector. */
    double* get_res_pad() { return res_pad; } /**< Returns the padded result vector. */
    Complex* get_col_vec_freq()
    {
        return col_vec_freq;
    } /**< Returns the column vector frequency. */
    Complex* get_row_vec_freq() { return row_vec_freq; } /**< Returns the row vector frequency. */
    Complex* get_col_vec_freq_tosi()
    {
        return col_vec_freq_tosi;
    } /**< Returns the column vector frequency in TOSI format. */
    Complex* get_row_vec_freq_tosi()
    {
        return row_vec_freq_tosi;
    } /**< Returns the row vector frequency in TOSI format. */
    Complex* get_mat_freq_tosi()
    {
        return mat_freq_tosi;
    } /**< Returns the matrix frequency in TOSI format. */
    Complex* get_mat_freq_tosi_other()
    {
        return mat_freq_tosi_other;
    } /**< Returns the other matrix frequency in TOSI format. */
    cufftHandle get_forward_plan()
    {
        return forward_plan;
    } /**< Returns the forward plan for FFT. */
    cufftHandle get_inverse_plan()
    {
        return inverse_plan;
    } /**< Returns the inverse plan for FFT. */
    cufftHandle get_forward_plan_conj()
    {
        return forward_plan_conj;
    } /**< Returns the forward plan for conjugate FFT. */
    cufftHandle get_inverse_plan_conj()
    {
        return inverse_plan_conj;
    } /**< Returns the inverse plan for conjugate FFT. */
    Comm& get_comm() { return comm; } /**< Returns reference to the communication object. */
    unsigned int get_num_cols()
    {
        return num_cols;
    } /**< Returns the number of columns in the matrix. */
    unsigned int get_num_rows()
    {
        return num_rows;
    } /**< Returns the number of rows in the matrix. */
    unsigned int get_glob_num_cols()
    {
        return glob_num_cols;
    } /**< Returns the global number of columns in the matrix. */
    unsigned int get_glob_num_rows()
    {
        return glob_num_rows;
    } /**< Returns the global number of rows in the matrix. */
    unsigned int get_padded_size()
    {
        return padded_size;
    } /**< Returns the padded block size of the matrix. */
    unsigned int get_block_size()
    {
        return block_size;
    } /**< Returns the unpadded block size of the matrix. */
    bool is_initialized()
    {
        return initialized;
    } /**< Returns true if the matrix is initialized, false otherwise. */
    bool get_has_mat_freq_tosi_other()
    {
        return has_mat_freq_tosi_other;
    } /**< Returns true if the other matrix frequency in TOSI format exists, false otherwise. */
};

#endif // __MATRIX_HPP__