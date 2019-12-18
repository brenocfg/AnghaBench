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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_txqsq {int /*<<< orphan*/  dma_fifo_pc; } ;
struct mlx5e_sq_dma {int type; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
typedef  enum mlx5e_dma_map_type { ____Placeholder_mlx5e_dma_map_type } mlx5e_dma_map_type ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct mlx5e_sq_dma* mlx5e_dma_get (struct mlx5e_txqsq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mlx5e_dma_push(struct mlx5e_txqsq *sq, dma_addr_t addr, u32 size,
	       enum mlx5e_dma_map_type map_type)
{
	struct mlx5e_sq_dma *dma = mlx5e_dma_get(sq, sq->dma_fifo_pc++);

	dma->addr = addr;
	dma->size = size;
	dma->type = map_type;
}