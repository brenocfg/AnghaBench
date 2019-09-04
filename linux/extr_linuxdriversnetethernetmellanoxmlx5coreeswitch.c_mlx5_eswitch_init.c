#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  encap; int /*<<< orphan*/  inline_mode; int /*<<< orphan*/  mod_hdr_tbl; int /*<<< orphan*/  encap_tbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  link_state; } ;
struct mlx5_vport {int vport; int total_vports; struct mlx5_vport* vports; scalar_t__ work_queue; TYPE_2__ offloads; int /*<<< orphan*/  mode; scalar_t__ enabled_vports; int /*<<< orphan*/  vport_change_handler; struct mlx5_core_dev* dev; TYPE_1__ info; int /*<<< orphan*/  state_lock; } ;
struct mlx5_eswitch {int vport; int total_vports; struct mlx5_eswitch* vports; scalar_t__ work_queue; TYPE_2__ offloads; int /*<<< orphan*/  mode; scalar_t__ enabled_vports; int /*<<< orphan*/  vport_change_handler; struct mlx5_core_dev* dev; TYPE_1__ info; int /*<<< orphan*/  state_lock; } ;
struct TYPE_6__ {struct mlx5_vport* eswitch; } ;
struct mlx5_core_dev {TYPE_3__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ESWITCH_ENCAP_MODE_BASIC ; 
 int /*<<< orphan*/  DEVLINK_ESWITCH_ENCAP_MODE_NONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ESW_FLOWTABLE_FDB (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_INLINE_MODE_NONE ; 
 int /*<<< orphan*/  MLX5_MAX_MC_PER_VPORT (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  MLX5_MAX_UC_PER_VPORT (struct mlx5_core_dev*) ; 
 int MLX5_TOTAL_VPORTS (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  MLX5_VPORT_ADMIN_STATE_AUTO ; 
 int /*<<< orphan*/  MLX5_VPORT_MANAGER (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  SRIOV_NONE ; 
 scalar_t__ create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  decap ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  encap ; 
 int /*<<< orphan*/  esw_info (struct mlx5_core_dev*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_offloads_cleanup_reps (struct mlx5_vport*) ; 
 int esw_offloads_init_reps (struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_change_handler ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 struct mlx5_vport* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_vport*) ; 
 struct mlx5_vport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_init(struct mlx5_core_dev *dev)
{
	int total_vports = MLX5_TOTAL_VPORTS(dev);
	struct mlx5_eswitch *esw;
	int vport_num;
	int err;

	if (!MLX5_VPORT_MANAGER(dev))
		return 0;

	esw_info(dev,
		 "Total vports %d, per vport: max uc(%d) max mc(%d)\n",
		 total_vports,
		 MLX5_MAX_UC_PER_VPORT(dev),
		 MLX5_MAX_MC_PER_VPORT(dev));

	esw = kzalloc(sizeof(*esw), GFP_KERNEL);
	if (!esw)
		return -ENOMEM;

	esw->dev = dev;

	esw->work_queue = create_singlethread_workqueue("mlx5_esw_wq");
	if (!esw->work_queue) {
		err = -ENOMEM;
		goto abort;
	}

	esw->vports = kcalloc(total_vports, sizeof(struct mlx5_vport),
			      GFP_KERNEL);
	if (!esw->vports) {
		err = -ENOMEM;
		goto abort;
	}

	err = esw_offloads_init_reps(esw);
	if (err)
		goto abort;

	hash_init(esw->offloads.encap_tbl);
	hash_init(esw->offloads.mod_hdr_tbl);
	mutex_init(&esw->state_lock);

	for (vport_num = 0; vport_num < total_vports; vport_num++) {
		struct mlx5_vport *vport = &esw->vports[vport_num];

		vport->vport = vport_num;
		vport->info.link_state = MLX5_VPORT_ADMIN_STATE_AUTO;
		vport->dev = dev;
		INIT_WORK(&vport->vport_change_handler,
			  esw_vport_change_handler);
	}

	esw->total_vports = total_vports;
	esw->enabled_vports = 0;
	esw->mode = SRIOV_NONE;
	esw->offloads.inline_mode = MLX5_INLINE_MODE_NONE;
	if (MLX5_CAP_ESW_FLOWTABLE_FDB(dev, encap) &&
	    MLX5_CAP_ESW_FLOWTABLE_FDB(dev, decap))
		esw->offloads.encap = DEVLINK_ESWITCH_ENCAP_MODE_BASIC;
	else
		esw->offloads.encap = DEVLINK_ESWITCH_ENCAP_MODE_NONE;

	dev->priv.eswitch = esw;
	return 0;
abort:
	if (esw->work_queue)
		destroy_workqueue(esw->work_queue);
	esw_offloads_cleanup_reps(esw);
	kfree(esw->vports);
	kfree(esw);
	return err;
}