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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ num_flows; int /*<<< orphan*/  inline_mode; } ;
struct mlx5_eswitch {int enabled_vports; TYPE_2__ offloads; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_ESWITCH_INLINE_MODE_NONE ; 
 int EOPNOTSUPP ; 
 int MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
#define  MLX5_CAP_INLINE_MODE_L2 130 
#define  MLX5_CAP_INLINE_MODE_NOT_REQUIRED 129 
#define  MLX5_CAP_INLINE_MODE_VPORT_CONTEXT 128 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int esw_inline_mode_from_devlink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esw_warn (struct mlx5_core_dev*,char*,...) ; 
 int mlx5_devlink_eswitch_check (struct devlink*) ; 
 int mlx5_modify_nic_vport_min_inline (struct mlx5_core_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqe_inline_mode ; 

int mlx5_devlink_eswitch_inline_mode_set(struct devlink *devlink, u8 mode)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	struct mlx5_eswitch *esw = dev->priv.eswitch;
	int err, vport;
	u8 mlx5_mode;

	err = mlx5_devlink_eswitch_check(devlink);
	if (err)
		return err;

	switch (MLX5_CAP_ETH(dev, wqe_inline_mode)) {
	case MLX5_CAP_INLINE_MODE_NOT_REQUIRED:
		if (mode == DEVLINK_ESWITCH_INLINE_MODE_NONE)
			return 0;
		/* fall through */
	case MLX5_CAP_INLINE_MODE_L2:
		esw_warn(dev, "Inline mode can't be set\n");
		return -EOPNOTSUPP;
	case MLX5_CAP_INLINE_MODE_VPORT_CONTEXT:
		break;
	}

	if (esw->offloads.num_flows > 0) {
		esw_warn(dev, "Can't set inline mode when flows are configured\n");
		return -EOPNOTSUPP;
	}

	err = esw_inline_mode_from_devlink(mode, &mlx5_mode);
	if (err)
		goto out;

	for (vport = 1; vport < esw->enabled_vports; vport++) {
		err = mlx5_modify_nic_vport_min_inline(dev, vport, mlx5_mode);
		if (err) {
			esw_warn(dev, "Failed to set min inline on vport %d\n",
				 vport);
			goto revert_inline_mode;
		}
	}

	esw->offloads.inline_mode = mlx5_mode;
	return 0;

revert_inline_mode:
	while (--vport > 0)
		mlx5_modify_nic_vport_min_inline(dev,
						 vport,
						 esw->offloads.inline_mode);
out:
	return err;
}