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
struct netlink_ext_ack {int dummy; } ;
struct TYPE_7__ {scalar_t__ inline_mode; } ;
struct mlx5_eswitch {scalar_t__ mode; TYPE_3__ offloads; TYPE_4__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_vfs; } ;
struct TYPE_6__ {TYPE_1__ sriov; } ;
struct TYPE_8__ {TYPE_2__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLX5_ESWITCH_LEGACY ; 
 scalar_t__ MLX5_ESWITCH_OFFLOADS ; 
 scalar_t__ MLX5_INLINE_MODE_L2 ; 
 scalar_t__ MLX5_INLINE_MODE_NONE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  mlx5_core_is_ecpf_esw_manager (TYPE_4__*) ; 
 int /*<<< orphan*/  mlx5_eswitch_disable (struct mlx5_eswitch*) ; 
 int mlx5_eswitch_enable (struct mlx5_eswitch*,scalar_t__) ; 
 scalar_t__ mlx5_eswitch_inline_mode_get (struct mlx5_eswitch*,scalar_t__*) ; 
 int /*<<< orphan*/  mlx5_eswitch_update_num_of_vfs (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esw_offloads_start(struct mlx5_eswitch *esw,
			      struct netlink_ext_ack *extack)
{
	int err, err1;

	if (esw->mode != MLX5_ESWITCH_LEGACY &&
	    !mlx5_core_is_ecpf_esw_manager(esw->dev)) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Can't set offloads mode, SRIOV legacy not enabled");
		return -EINVAL;
	}

	mlx5_eswitch_disable(esw);
	mlx5_eswitch_update_num_of_vfs(esw, esw->dev->priv.sriov.num_vfs);
	err = mlx5_eswitch_enable(esw, MLX5_ESWITCH_OFFLOADS);
	if (err) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Failed setting eswitch to offloads");
		err1 = mlx5_eswitch_enable(esw, MLX5_ESWITCH_LEGACY);
		if (err1) {
			NL_SET_ERR_MSG_MOD(extack,
					   "Failed setting eswitch back to legacy");
		}
	}
	if (esw->offloads.inline_mode == MLX5_INLINE_MODE_NONE) {
		if (mlx5_eswitch_inline_mode_get(esw,
						 &esw->offloads.inline_mode)) {
			esw->offloads.inline_mode = MLX5_INLINE_MODE_L2;
			NL_SET_ERR_MSG_MOD(extack,
					   "Inline mode is different between vports");
		}
	}
	return err;
}