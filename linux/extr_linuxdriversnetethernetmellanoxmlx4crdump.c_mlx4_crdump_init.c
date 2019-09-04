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
struct pci_dev {int dummy; } ;
struct mlx4_fw_crdump {int snapshot_enable; void* region_fw_health; void* region_crspace; } ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {struct pci_dev* pdev; struct mlx4_fw_crdump crdump; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEALTH_BUFFER_SIZE ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MAX_NUM_OF_DUMPS_TO_STORE ; 
 int /*<<< orphan*/  PTR_ERR (void*) ; 
 void* devlink_region_create (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  region_cr_space_str ; 
 int /*<<< orphan*/  region_fw_health_str ; 

int mlx4_crdump_init(struct mlx4_dev *dev)
{
	struct devlink *devlink = priv_to_devlink(mlx4_priv(dev));
	struct mlx4_fw_crdump *crdump = &dev->persist->crdump;
	struct pci_dev *pdev = dev->persist->pdev;

	crdump->snapshot_enable = false;

	/* Create cr-space region */
	crdump->region_crspace =
		devlink_region_create(devlink,
				      region_cr_space_str,
				      MAX_NUM_OF_DUMPS_TO_STORE,
				      pci_resource_len(pdev, 0));
	if (IS_ERR(crdump->region_crspace))
		mlx4_warn(dev, "crdump: create devlink region %s err %ld\n",
			  region_cr_space_str,
			  PTR_ERR(crdump->region_crspace));

	/* Create fw-health region */
	crdump->region_fw_health =
		devlink_region_create(devlink,
				      region_fw_health_str,
				      MAX_NUM_OF_DUMPS_TO_STORE,
				      HEALTH_BUFFER_SIZE);
	if (IS_ERR(crdump->region_fw_health))
		mlx4_warn(dev, "crdump: create devlink region %s err %ld\n",
			  region_fw_health_str,
			  PTR_ERR(crdump->region_fw_health));

	return 0;
}