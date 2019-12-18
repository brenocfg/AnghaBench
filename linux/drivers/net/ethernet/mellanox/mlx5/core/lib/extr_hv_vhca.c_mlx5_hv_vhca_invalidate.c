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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_hv_vhca_work {int /*<<< orphan*/  invalidate_work; int /*<<< orphan*/  block_mask; struct mlx5_hv_vhca* hv_vhca; } ;
struct mlx5_hv_vhca {int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_hv_vhca_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_hv_vhca_invalidate_work ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5_hv_vhca_invalidate(void *context, u64 block_mask)
{
	struct mlx5_hv_vhca *hv_vhca = (struct mlx5_hv_vhca *)context;
	struct mlx5_hv_vhca_work *work;

	work = kzalloc(sizeof(*work), GFP_ATOMIC);
	if (!work)
		return;

	INIT_WORK(&work->invalidate_work, mlx5_hv_vhca_invalidate_work);
	work->hv_vhca    = hv_vhca;
	work->block_mask = block_mask;

	queue_work(hv_vhca->work_queue, &work->invalidate_work);
}