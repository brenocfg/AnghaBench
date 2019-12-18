#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  encap_tbl_lock; TYPE_1__ mod_hdr; } ;
struct mlx5_eswitch {struct mlx5_eswitch* vports; TYPE_2__ offloads; int /*<<< orphan*/  work_queue; TYPE_4__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * eswitch; } ;
struct TYPE_9__ {TYPE_3__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_MANAGER (TYPE_4__*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_info (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  esw_offloads_cleanup_reps (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void mlx5_eswitch_cleanup(struct mlx5_eswitch *esw)
{
	if (!esw || !MLX5_VPORT_MANAGER(esw->dev))
		return;

	esw_info(esw->dev, "cleanup\n");

	esw->dev->priv.eswitch = NULL;
	destroy_workqueue(esw->work_queue);
	esw_offloads_cleanup_reps(esw);
	mutex_destroy(&esw->offloads.mod_hdr.lock);
	mutex_destroy(&esw->offloads.encap_tbl_lock);
	kfree(esw->vports);
	kfree(esw);
}