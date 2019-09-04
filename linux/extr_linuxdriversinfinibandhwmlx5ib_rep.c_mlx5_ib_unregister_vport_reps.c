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
struct mlx5_eswitch {int dummy; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  REP_IB ; 
 int /*<<< orphan*/  mlx5_eswitch_unregister_vport_rep (struct mlx5_eswitch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_rep_unregister_vf_vports (struct mlx5_ib_dev*) ; 

void mlx5_ib_unregister_vport_reps(struct mlx5_ib_dev *dev)
{
	struct mlx5_eswitch *esw   = dev->mdev->priv.eswitch;

	mlx5_ib_rep_unregister_vf_vports(dev); /* VFs vports */
	mlx5_eswitch_unregister_vport_rep(esw, 0, REP_IB); /* UPLINK PF*/
}