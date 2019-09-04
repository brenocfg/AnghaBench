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
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_eswitch_rep_if {int /*<<< orphan*/  get_proto_dev; int /*<<< orphan*/  unload; int /*<<< orphan*/  load; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_2__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int MLX5_TOTAL_VPORTS (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  REP_ETH ; 
 int /*<<< orphan*/  mlx5_eswitch_register_vport_rep (struct mlx5_eswitch*,int,struct mlx5_eswitch_rep_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_vport_rep_get_proto_dev ; 
 int /*<<< orphan*/  mlx5e_vport_rep_load ; 
 int /*<<< orphan*/  mlx5e_vport_rep_unload ; 

__attribute__((used)) static void mlx5e_rep_register_vf_vports(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	struct mlx5_eswitch *esw   = mdev->priv.eswitch;
	int total_vfs = MLX5_TOTAL_VPORTS(mdev);
	int vport;

	for (vport = 1; vport < total_vfs; vport++) {
		struct mlx5_eswitch_rep_if rep_if = {};

		rep_if.load = mlx5e_vport_rep_load;
		rep_if.unload = mlx5e_vport_rep_unload;
		rep_if.get_proto_dev = mlx5e_vport_rep_get_proto_dev;
		mlx5_eswitch_register_vport_rep(esw, vport, &rep_if, REP_ETH);
	}
}