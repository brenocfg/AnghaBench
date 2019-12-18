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
struct mlx5_core_sriov {TYPE_1__* vfs_ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  vfs_pages; int /*<<< orphan*/  eswitch; struct mlx5_core_sriov sriov; } ;
struct mlx5_core_dev {TYPE_2__ priv; int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_MANAGER (struct mlx5_core_dev*) ; 
 int mlx5_core_disable_hca (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_eswitch_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_wait_for_pages (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int pci_num_vf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_device_disable_sriov(struct mlx5_core_dev *dev)
{
	struct mlx5_core_sriov *sriov = &dev->priv.sriov;
	int num_vfs = pci_num_vf(dev->pdev);
	int err;
	int vf;

	for (vf = num_vfs - 1; vf >= 0; vf--) {
		if (!sriov->vfs_ctx[vf].enabled)
			continue;
		err = mlx5_core_disable_hca(dev, vf + 1);
		if (err) {
			mlx5_core_warn(dev, "failed to disable VF %d\n", vf);
			continue;
		}
		sriov->vfs_ctx[vf].enabled = 0;
	}

	if (MLX5_ESWITCH_MANAGER(dev))
		mlx5_eswitch_disable(dev->priv.eswitch);

	if (mlx5_wait_for_pages(dev, &dev->priv.vfs_pages))
		mlx5_core_warn(dev, "timeout reclaiming VFs pages\n");
}