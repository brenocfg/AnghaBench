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
struct mlx5_core_sriov {scalar_t__ enabled_vfs; TYPE_2__* vfs_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  eswitch; struct mlx5_core_sriov sriov; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct TYPE_4__ {int enabled; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_IB ; 
 int /*<<< orphan*/  MLX5_ESWITCH_MANAGER (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  SRIOV_LEGACY ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_core_enable_hca (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,...) ; 
 int mlx5_eswitch_enable_sriov (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_type ; 
 int sriov_restore_guids (struct mlx5_core_dev*,int) ; 

__attribute__((used)) static int mlx5_device_enable_sriov(struct mlx5_core_dev *dev, int num_vfs)
{
	struct mlx5_core_sriov *sriov = &dev->priv.sriov;
	int err;
	int vf;

	if (sriov->enabled_vfs) {
		mlx5_core_warn(dev,
			       "failed to enable SRIOV on device, already enabled with %d vfs\n",
			       sriov->enabled_vfs);
		return -EBUSY;
	}

	if (!MLX5_ESWITCH_MANAGER(dev))
		goto enable_vfs_hca;

	err = mlx5_eswitch_enable_sriov(dev->priv.eswitch, num_vfs, SRIOV_LEGACY);
	if (err) {
		mlx5_core_warn(dev,
			       "failed to enable eswitch SRIOV (%d)\n", err);
		return err;
	}

enable_vfs_hca:
	for (vf = 0; vf < num_vfs; vf++) {
		err = mlx5_core_enable_hca(dev, vf + 1);
		if (err) {
			mlx5_core_warn(dev, "failed to enable VF %d (%d)\n", vf, err);
			continue;
		}
		sriov->vfs_ctx[vf].enabled = 1;
		sriov->enabled_vfs++;
		if (MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_IB) {
			err = sriov_restore_guids(dev, vf);
			if (err) {
				mlx5_core_warn(dev,
					       "failed to restore VF %d settings, err %d\n",
					       vf, err);
				continue;
			}
		}
		mlx5_core_dbg(dev, "successfully enabled VF* %d\n", vf);
	}

	return 0;
}