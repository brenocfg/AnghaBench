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
struct TYPE_2__ {int /*<<< orphan*/  encap; } ;
struct mlx5_eswitch {TYPE_1__ offloads; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ESWITCH_ENCAP_MODE_NONE ; 
 int /*<<< orphan*/  esw_offloads_devcom_cleanup (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_offloads_steering_cleanup (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_offloads_unload_all_reps (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_set_passing_vport_metadata (struct mlx5_eswitch*,int) ; 
 int /*<<< orphan*/  mlx5_eswitch_disable_pf_vf_vports (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_rdma_disable_roce (int /*<<< orphan*/ ) ; 

void esw_offloads_disable(struct mlx5_eswitch *esw)
{
	esw_offloads_devcom_cleanup(esw);
	esw_offloads_unload_all_reps(esw);
	mlx5_eswitch_disable_pf_vf_vports(esw);
	esw_set_passing_vport_metadata(esw, false);
	esw_offloads_steering_cleanup(esw);
	mlx5_rdma_disable_roce(esw->dev);
	esw->offloads.encap = DEVLINK_ESWITCH_ENCAP_MODE_NONE;
}