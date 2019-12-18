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
struct mlx5e_rq {scalar_t__ umem; } ;
struct mlx5e_dma_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_page_release_dynamic (struct mlx5e_rq*,struct mlx5e_dma_info*,int) ; 
 int /*<<< orphan*/  mlx5e_xsk_page_release (struct mlx5e_rq*,struct mlx5e_dma_info*) ; 

__attribute__((used)) static inline void mlx5e_page_release(struct mlx5e_rq *rq,
				      struct mlx5e_dma_info *dma_info,
				      bool recycle)
{
	if (rq->umem)
		/* The `recycle` parameter is ignored, and the page is always
		 * put into the Reuse Ring, because there is no way to return
		 * the page to the userspace when the interface goes down.
		 */
		mlx5e_xsk_page_release(rq, dma_info);
	else
		mlx5e_page_release_dynamic(rq, dma_info, recycle);
}