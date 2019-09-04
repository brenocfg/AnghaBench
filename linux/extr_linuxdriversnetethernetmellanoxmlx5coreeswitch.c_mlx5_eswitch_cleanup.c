#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_eswitch {struct mlx5_eswitch* vports; int /*<<< orphan*/  work_queue; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * eswitch; } ;
struct TYPE_5__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_MANAGER (TYPE_2__*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  esw_offloads_cleanup_reps (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_eswitch*) ; 

void mlx5_eswitch_cleanup(struct mlx5_eswitch *esw)
{
	if (!esw || !MLX5_VPORT_MANAGER(esw->dev))
		return;

	esw_info(esw->dev, "cleanup\n");

	esw->dev->priv.eswitch = NULL;
	destroy_workqueue(esw->work_queue);
	esw_offloads_cleanup_reps(esw);
	kfree(esw->vports);
	kfree(esw);
}