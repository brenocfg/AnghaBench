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
struct mlx5e_rq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
struct mlx5e_dma_info {TYPE_1__ xsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_xsk_recycle_frame (struct mlx5e_rq*,int /*<<< orphan*/ ) ; 

void mlx5e_xsk_page_release(struct mlx5e_rq *rq,
			    struct mlx5e_dma_info *dma_info)
{
	mlx5e_xsk_recycle_frame(rq, dma_info->xsk.handle);
}