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
struct TYPE_2__ {int /*<<< orphan*/  termtbl_mutex; int /*<<< orphan*/  encap; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; TYPE_1__ offloads; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ESWITCH_ENCAP_MODE_BASIC ; 
 int /*<<< orphan*/  DEVLINK_ESWITCH_ENCAP_MODE_NONE ; 
 scalar_t__ MLX5_CAP_ESW_FLOWTABLE_FDB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_VPORT_UC_ADDR_CHANGE ; 
 int /*<<< orphan*/  decap ; 
 int /*<<< orphan*/  esw_offloads_devcom_init (struct mlx5_eswitch*) ; 
 int esw_offloads_load_all_reps (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_offloads_steering_cleanup (struct mlx5_eswitch*) ; 
 int esw_offloads_steering_init (struct mlx5_eswitch*) ; 
 int esw_set_passing_vport_metadata (struct mlx5_eswitch*,int) ; 
 int /*<<< orphan*/  mlx5_eswitch_disable_pf_vf_vports (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_eswitch_enable_pf_vf_vports (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_rdma_disable_roce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_rdma_enable_roce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reformat ; 

int esw_offloads_enable(struct mlx5_eswitch *esw)
{
	int err;

	if (MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, reformat) &&
	    MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, decap))
		esw->offloads.encap = DEVLINK_ESWITCH_ENCAP_MODE_BASIC;
	else
		esw->offloads.encap = DEVLINK_ESWITCH_ENCAP_MODE_NONE;

	mlx5_rdma_enable_roce(esw->dev);
	err = esw_offloads_steering_init(esw);
	if (err)
		goto err_steering_init;

	err = esw_set_passing_vport_metadata(esw, true);
	if (err)
		goto err_vport_metadata;

	mlx5_eswitch_enable_pf_vf_vports(esw, MLX5_VPORT_UC_ADDR_CHANGE);

	err = esw_offloads_load_all_reps(esw);
	if (err)
		goto err_reps;

	esw_offloads_devcom_init(esw);
	mutex_init(&esw->offloads.termtbl_mutex);

	return 0;

err_reps:
	mlx5_eswitch_disable_pf_vf_vports(esw);
	esw_set_passing_vport_metadata(esw, false);
err_vport_metadata:
	esw_offloads_steering_cleanup(esw);
err_steering_init:
	mlx5_rdma_disable_roce(esw->dev);
	return err;
}