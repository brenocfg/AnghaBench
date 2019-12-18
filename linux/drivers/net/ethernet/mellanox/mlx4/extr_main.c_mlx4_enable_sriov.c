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
typedef  int u8 ;
typedef  int u64 ;
struct pci_dev {int dummy; } ;
struct mlx4_dev {int flags; int /*<<< orphan*/ * dev_vfs; TYPE_1__* persist; } ;
struct TYPE_2__ {int num_vfs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX4_FLAG_MASTER ; 
 int MLX4_FLAG_SLAVE ; 
 int MLX4_FLAG_SRIOV ; 
 int /*<<< orphan*/  MLX4_MAX_NUM_VF ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_sriov_get_totalvfs (struct pci_dev*) ; 
 int /*<<< orphan*/  pf_loading ; 

__attribute__((used)) static u64 mlx4_enable_sriov(struct mlx4_dev *dev, struct pci_dev *pdev,
			     u8 total_vfs, int existing_vfs, int reset_flow)
{
	u64 dev_flags = dev->flags;
	int err = 0;
	int fw_enabled_sriov_vfs = min(pci_sriov_get_totalvfs(pdev),
					MLX4_MAX_NUM_VF);

	if (reset_flow) {
		dev->dev_vfs = kcalloc(total_vfs, sizeof(*dev->dev_vfs),
				       GFP_KERNEL);
		if (!dev->dev_vfs)
			goto free_mem;
		return dev_flags;
	}

	atomic_inc(&pf_loading);
	if (dev->flags &  MLX4_FLAG_SRIOV) {
		if (existing_vfs != total_vfs) {
			mlx4_err(dev, "SR-IOV was already enabled, but with num_vfs (%d) different than requested (%d)\n",
				 existing_vfs, total_vfs);
			total_vfs = existing_vfs;
		}
	}

	dev->dev_vfs = kcalloc(total_vfs, sizeof(*dev->dev_vfs), GFP_KERNEL);
	if (NULL == dev->dev_vfs) {
		mlx4_err(dev, "Failed to allocate memory for VFs\n");
		goto disable_sriov;
	}

	if (!(dev->flags &  MLX4_FLAG_SRIOV)) {
		if (total_vfs > fw_enabled_sriov_vfs) {
			mlx4_err(dev, "requested vfs (%d) > available vfs (%d). Continuing without SR_IOV\n",
				 total_vfs, fw_enabled_sriov_vfs);
			err = -ENOMEM;
			goto disable_sriov;
		}
		mlx4_warn(dev, "Enabling SR-IOV with %d VFs\n", total_vfs);
		err = pci_enable_sriov(pdev, total_vfs);
	}
	if (err) {
		mlx4_err(dev, "Failed to enable SR-IOV, continuing without SR-IOV (err = %d)\n",
			 err);
		goto disable_sriov;
	} else {
		mlx4_warn(dev, "Running in master mode\n");
		dev_flags |= MLX4_FLAG_SRIOV |
			MLX4_FLAG_MASTER;
		dev_flags &= ~MLX4_FLAG_SLAVE;
		dev->persist->num_vfs = total_vfs;
	}
	return dev_flags;

disable_sriov:
	atomic_dec(&pf_loading);
free_mem:
	dev->persist->num_vfs = 0;
	kfree(dev->dev_vfs);
	dev->dev_vfs = NULL;
	return dev_flags & ~MLX4_FLAG_MASTER;
}