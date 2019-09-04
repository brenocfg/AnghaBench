#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ inline_mode; } ;
struct mlx5_eswitch {scalar_t__ mode; TYPE_4__* dev; TYPE_1__ offloads; } ;
struct TYPE_7__ {int num_vfs; } ;
struct TYPE_6__ {TYPE_3__ sriov; } ;
struct TYPE_8__ {TYPE_2__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLX5_INLINE_MODE_L2 ; 
 scalar_t__ MLX5_INLINE_MODE_NONE ; 
 scalar_t__ SRIOV_LEGACY ; 
 scalar_t__ SRIOV_OFFLOADS ; 
 int /*<<< orphan*/  esw_warn (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  mlx5_eswitch_disable_sriov (struct mlx5_eswitch*) ; 
 int mlx5_eswitch_enable_sriov (struct mlx5_eswitch*,int,scalar_t__) ; 
 scalar_t__ mlx5_eswitch_inline_mode_get (struct mlx5_eswitch*,int,scalar_t__*) ; 

__attribute__((used)) static int esw_offloads_start(struct mlx5_eswitch *esw)
{
	int err, err1, num_vfs = esw->dev->priv.sriov.num_vfs;

	if (esw->mode != SRIOV_LEGACY) {
		esw_warn(esw->dev, "Can't set offloads mode, SRIOV legacy not enabled\n");
		return -EINVAL;
	}

	mlx5_eswitch_disable_sriov(esw);
	err = mlx5_eswitch_enable_sriov(esw, num_vfs, SRIOV_OFFLOADS);
	if (err) {
		esw_warn(esw->dev, "Failed setting eswitch to offloads, err %d\n", err);
		err1 = mlx5_eswitch_enable_sriov(esw, num_vfs, SRIOV_LEGACY);
		if (err1)
			esw_warn(esw->dev, "Failed setting eswitch back to legacy, err %d\n", err1);
	}
	if (esw->offloads.inline_mode == MLX5_INLINE_MODE_NONE) {
		if (mlx5_eswitch_inline_mode_get(esw,
						 num_vfs,
						 &esw->offloads.inline_mode)) {
			esw->offloads.inline_mode = MLX5_INLINE_MODE_L2;
			esw_warn(esw->dev, "Inline mode is different between vports\n");
		}
	}
	return err;
}