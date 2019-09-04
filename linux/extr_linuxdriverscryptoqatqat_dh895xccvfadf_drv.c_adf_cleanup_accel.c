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
struct adf_bar {scalar_t__ virt_addr; } ;
struct adf_accel_pci {TYPE_1__* pci_dev; struct adf_bar* pci_bars; } ;
struct adf_accel_dev {int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/ * hw_device; struct adf_accel_pci accel_pci_dev; } ;
struct TYPE_2__ {int device; int /*<<< orphan*/  physfn; } ;

/* Variables and functions */
#define  ADF_DH895XCCIOV_PCI_DEVICE_ID 128 
 int ADF_PCI_MAX_BARS ; 
 int /*<<< orphan*/  adf_cfg_dev_remove (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  adf_clean_hw_data_dh895xcciov (int /*<<< orphan*/ *) ; 
 struct adf_accel_dev* adf_devmgr_pci_to_accel_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adf_devmgr_rm_dev (struct adf_accel_dev*,struct adf_accel_dev*) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void adf_cleanup_accel(struct adf_accel_dev *accel_dev)
{
	struct adf_accel_pci *accel_pci_dev = &accel_dev->accel_pci_dev;
	struct adf_accel_dev *pf;
	int i;

	for (i = 0; i < ADF_PCI_MAX_BARS; i++) {
		struct adf_bar *bar = &accel_pci_dev->pci_bars[i];

		if (bar->virt_addr)
			pci_iounmap(accel_pci_dev->pci_dev, bar->virt_addr);
	}

	if (accel_dev->hw_device) {
		switch (accel_pci_dev->pci_dev->device) {
		case ADF_DH895XCCIOV_PCI_DEVICE_ID:
			adf_clean_hw_data_dh895xcciov(accel_dev->hw_device);
			break;
		default:
			break;
		}
		kfree(accel_dev->hw_device);
		accel_dev->hw_device = NULL;
	}
	adf_cfg_dev_remove(accel_dev);
	debugfs_remove(accel_dev->debugfs_dir);
	pf = adf_devmgr_pci_to_accel_dev(accel_pci_dev->pci_dev->physfn);
	adf_devmgr_rm_dev(accel_dev, pf);
}