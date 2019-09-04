#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx5_eswitch {TYPE_3__* dev; } ;
struct TYPE_5__ {int num_vfs; } ;
struct TYPE_6__ {TYPE_1__ sriov; } ;
struct TYPE_7__ {TYPE_2__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_INTERFACE_PROTOCOL_IB ; 
 int /*<<< orphan*/  SRIOV_LEGACY ; 
 int /*<<< orphan*/  SRIOV_OFFLOADS ; 
 int /*<<< orphan*/  esw_warn (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  mlx5_eswitch_disable_sriov (struct mlx5_eswitch*) ; 
 int mlx5_eswitch_enable_sriov (struct mlx5_eswitch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_reload_interface (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esw_offloads_stop(struct mlx5_eswitch *esw)
{
	int err, err1, num_vfs = esw->dev->priv.sriov.num_vfs;

	mlx5_eswitch_disable_sriov(esw);
	err = mlx5_eswitch_enable_sriov(esw, num_vfs, SRIOV_LEGACY);
	if (err) {
		esw_warn(esw->dev, "Failed setting eswitch to legacy, err %d\n", err);
		err1 = mlx5_eswitch_enable_sriov(esw, num_vfs, SRIOV_OFFLOADS);
		if (err1)
			esw_warn(esw->dev, "Failed setting eswitch back to offloads, err %d\n", err);
	}

	/* enable back PF RoCE */
	mlx5_reload_interface(esw->dev, MLX5_INTERFACE_PROTOCOL_IB);

	return err;
}