#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_6__* slave_list; TYPE_2__* res_alloc; } ;
struct TYPE_10__ {TYPE_3__ res_tracker; } ;
struct TYPE_11__ {TYPE_4__ master; } ;
struct mlx4_priv {TYPE_5__ mfunc; } ;
struct TYPE_7__ {int function; } ;
struct mlx4_dev {int num_slaves; TYPE_1__ caps; } ;
typedef  enum mlx4_res_tracker_free_type { ____Placeholder_mlx4_res_tracker_free_type } mlx4_res_tracker_free_type ;
struct TYPE_12__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {TYPE_6__* quota; TYPE_6__* guaranteed; TYPE_6__* allocated; } ;

/* Variables and functions */
 int MLX4_NUM_OF_RESOURCE_TYPE ; 
 int RES_TR_FREE_ALL ; 
 int RES_TR_FREE_SLAVES_ONLY ; 
 int RES_TR_FREE_STRUCTS_ONLY ; 
 int /*<<< orphan*/  kfree (TYPE_6__*) ; 
 int /*<<< orphan*/  mlx4_delete_all_resources_for_slave (struct mlx4_dev*,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_reset_roce_gids (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rem_slave_vlans (struct mlx4_dev*,int) ; 

void mlx4_free_resource_tracker(struct mlx4_dev *dev,
				enum mlx4_res_tracker_free_type type)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int i;

	if (priv->mfunc.master.res_tracker.slave_list) {
		if (type != RES_TR_FREE_STRUCTS_ONLY) {
			for (i = 0; i < dev->num_slaves; i++) {
				if (type == RES_TR_FREE_ALL ||
				    dev->caps.function != i)
					mlx4_delete_all_resources_for_slave(dev, i);
			}
			/* free master's vlans */
			i = dev->caps.function;
			mlx4_reset_roce_gids(dev, i);
			mutex_lock(&priv->mfunc.master.res_tracker.slave_list[i].mutex);
			rem_slave_vlans(dev, i);
			mutex_unlock(&priv->mfunc.master.res_tracker.slave_list[i].mutex);
		}

		if (type != RES_TR_FREE_SLAVES_ONLY) {
			for (i = 0; i < MLX4_NUM_OF_RESOURCE_TYPE; i++) {
				kfree(priv->mfunc.master.res_tracker.res_alloc[i].allocated);
				priv->mfunc.master.res_tracker.res_alloc[i].allocated = NULL;
				kfree(priv->mfunc.master.res_tracker.res_alloc[i].guaranteed);
				priv->mfunc.master.res_tracker.res_alloc[i].guaranteed = NULL;
				kfree(priv->mfunc.master.res_tracker.res_alloc[i].quota);
				priv->mfunc.master.res_tracker.res_alloc[i].quota = NULL;
			}
			kfree(priv->mfunc.master.res_tracker.slave_list);
			priv->mfunc.master.res_tracker.slave_list = NULL;
		}
	}
}