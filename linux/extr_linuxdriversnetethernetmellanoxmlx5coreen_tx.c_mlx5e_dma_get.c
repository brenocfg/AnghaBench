#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_2__ {struct mlx5e_sq_dma* dma_fifo; } ;
struct mlx5e_txqsq {size_t dma_fifo_mask; TYPE_1__ db; } ;
struct mlx5e_sq_dma {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mlx5e_sq_dma *mlx5e_dma_get(struct mlx5e_txqsq *sq, u32 i)
{
	return &sq->db.dma_fifo[i & sq->dma_fifo_mask];
}