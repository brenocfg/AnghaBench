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
 int MLX5_TOTAL_VPORTS (TYPE_2__*) ; 
 int /*<<< orphan*/  REP_IB ; 
 int /*<<< orphan*/  mlx5_eswitch_unregister_vport_rep (struct mlx5_eswitch*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_ib_rep_unregister_vf_vports(struct mlx5_ib_dev *dev)
{
	struct mlx5_eswitch *esw   = dev->mdev->priv.eswitch;
	int total_vfs = MLX5_TOTAL_VPORTS(dev->mdev);
	int vport;

	for (vport = 1; vport < total_vfs; vport++)
		mlx5_eswitch_unregister_vport_rep(esw, vport, REP_IB);
}