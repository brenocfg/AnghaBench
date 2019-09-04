#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_ib_dev {TYPE_2__* mdev; } ;
struct mlx5_eswitch_rep_if {struct mlx5_ib_dev* priv; int /*<<< orphan*/  get_proto_dev; int /*<<< orphan*/  unload; int /*<<< orphan*/  load; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  REP_IB ; 
 int /*<<< orphan*/  mlx5_eswitch_register_vport_rep (struct mlx5_eswitch*,int /*<<< orphan*/ ,struct mlx5_eswitch_rep_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_nic_rep_load ; 
 int /*<<< orphan*/  mlx5_ib_nic_rep_unload ; 
 int /*<<< orphan*/  mlx5_ib_rep_register_vf_vports (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_vport_get_proto_dev ; 

void mlx5_ib_register_vport_reps(struct mlx5_ib_dev *dev)
{
	struct mlx5_eswitch *esw = dev->mdev->priv.eswitch;
	struct mlx5_eswitch_rep_if rep_if = {};

	rep_if.load = mlx5_ib_nic_rep_load;
	rep_if.unload = mlx5_ib_nic_rep_unload;
	rep_if.get_proto_dev = mlx5_ib_vport_get_proto_dev;
	rep_if.priv = dev;

	mlx5_eswitch_register_vport_rep(esw, 0, &rep_if, REP_IB);

	mlx5_ib_rep_register_vf_vports(dev);
}