#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ MLX5_CQE_SYNDROME_LOCAL_LENGTH_ERR ; 
 scalar_t__ MLX5_CQE_SYNDROME_LOCAL_PROT_ERR ; 
 scalar_t__ MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR ; 
 scalar_t__ MLX5_CQE_SYNDROME_WR_FLUSH_ERR ; 

__attribute__((used)) static inline bool cqe_syndrome_needs_recover(u8 syndrome)
{
	return syndrome == MLX5_CQE_SYNDROME_LOCAL_LENGTH_ERR ||
	       syndrome == MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR ||
	       syndrome == MLX5_CQE_SYNDROME_LOCAL_PROT_ERR ||
	       syndrome == MLX5_CQE_SYNDROME_WR_FLUSH_ERR;
}