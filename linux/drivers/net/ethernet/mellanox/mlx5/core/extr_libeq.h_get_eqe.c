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
typedef  int u32 ;
struct mlx5_eqe {int dummy; } ;
struct mlx5_eq {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int MLX5_EQE_SIZE ; 
 struct mlx5_eqe* mlx5_buf_offset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline struct mlx5_eqe *get_eqe(struct mlx5_eq *eq, u32 entry)
{
	return mlx5_buf_offset(&eq->buf, entry * MLX5_EQE_SIZE);
}