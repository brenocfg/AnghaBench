#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qlcnic_adapter {int flags; int drv_sds_rings; int drv_tx_rings; TYPE_1__* ahw; TYPE_2__* msix_entries; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct msix_entry {int dummy; } ;
struct TYPE_5__ {int entry; } ;
struct TYPE_4__ {int num_msix; scalar_t__ msix_supported; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLCNIC_82XX_MINIMUM_VECTOR ; 
 int QLCNIC_83XX_MINIMUM_VECTOR ; 
 int QLCNIC_MSIX_ENABLED ; 
 int QLCNIC_MSI_ENABLED ; 
 int QLCNIC_SINGLE_RING ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int pci_enable_msix_range (struct pci_dev*,TYPE_2__*,int,int) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_check_multi_tx (struct qlcnic_adapter*) ; 
 int rounddown_pow_of_two (int) ; 

int qlcnic_enable_msix(struct qlcnic_adapter *adapter, u32 num_msix)
{
	struct pci_dev *pdev = adapter->pdev;
	int err, vector;

	if (!adapter->msix_entries) {
		adapter->msix_entries = kcalloc(num_msix,
						sizeof(struct msix_entry),
						GFP_KERNEL);
		if (!adapter->msix_entries)
			return -ENOMEM;
	}

	adapter->flags &= ~(QLCNIC_MSI_ENABLED | QLCNIC_MSIX_ENABLED);

	if (adapter->ahw->msix_supported) {
enable_msix:
		for (vector = 0; vector < num_msix; vector++)
			adapter->msix_entries[vector].entry = vector;

		err = pci_enable_msix_range(pdev,
					    adapter->msix_entries, 1, num_msix);

		if (err == num_msix) {
			adapter->flags |= QLCNIC_MSIX_ENABLED;
			adapter->ahw->num_msix = num_msix;
			dev_info(&pdev->dev, "using msi-x interrupts\n");
			return 0;
		} else if (err > 0) {
			pci_disable_msix(pdev);

			dev_info(&pdev->dev,
				 "Unable to allocate %d MSI-X vectors, Available vectors %d\n",
				 num_msix, err);

			if (qlcnic_82xx_check(adapter)) {
				num_msix = rounddown_pow_of_two(err);
				if (err < QLCNIC_82XX_MINIMUM_VECTOR)
					return -ENOSPC;
			} else {
				num_msix = rounddown_pow_of_two(err - 1);
				num_msix += 1;
				if (err < QLCNIC_83XX_MINIMUM_VECTOR)
					return -ENOSPC;
			}

			if (qlcnic_82xx_check(adapter) &&
			    !qlcnic_check_multi_tx(adapter)) {
				adapter->drv_sds_rings = num_msix;
				adapter->drv_tx_rings = QLCNIC_SINGLE_RING;
			} else {
				/* Distribute vectors equally */
				adapter->drv_tx_rings = num_msix / 2;
				adapter->drv_sds_rings = adapter->drv_tx_rings;
			}

			if (num_msix) {
				dev_info(&pdev->dev,
					 "Trying to allocate %d MSI-X interrupt vectors\n",
					 num_msix);
				goto enable_msix;
			}
		} else {
			dev_info(&pdev->dev,
				 "Unable to allocate %d MSI-X vectors, err=%d\n",
				 num_msix, err);
			return err;
		}
	}

	return -EIO;
}