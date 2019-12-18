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
typedef  size_t u32 ;
struct mlx5e_xdp_info_fifo {size_t mask; struct mlx5e_xdp_info* xi; int /*<<< orphan*/ * pc; } ;
struct mlx5e_xdp_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
mlx5e_xdpi_fifo_push(struct mlx5e_xdp_info_fifo *fifo,
		     struct mlx5e_xdp_info *xi)
{
	u32 i = (*fifo->pc)++ & fifo->mask;

	fifo->xi[i] = *xi;
}