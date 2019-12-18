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
struct qlcnic_adapter {int drv_tss_rings; int drv_tx_rings; int drv_rss_rings; int drv_sds_rings; TYPE_1__* ahw; int /*<<< orphan*/  netdev; TYPE_2__* msix_entries; int /*<<< orphan*/  flags; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct msix_entry {int dummy; } ;
struct TYPE_5__ {int entry; } ;
struct TYPE_4__ {int num_msix; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QLCNIC_TSS_RSS ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int pci_enable_msix_exact (struct pci_dev*,TYPE_2__*,int) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 

int qlcnic_setup_tss_rss_intr(struct qlcnic_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	int num_msix = 0, err = 0, vector;

	adapter->flags &= ~QLCNIC_TSS_RSS;

	if (adapter->drv_tss_rings > 0)
		num_msix += adapter->drv_tss_rings;
	else
		num_msix += adapter->drv_tx_rings;

	if (adapter->drv_rss_rings > 0)
		num_msix += adapter->drv_rss_rings;
	else
		num_msix += adapter->drv_sds_rings;

	if (qlcnic_83xx_check(adapter))
		num_msix += 1;

	if (!adapter->msix_entries) {
		adapter->msix_entries = kcalloc(num_msix,
						sizeof(struct msix_entry),
						GFP_KERNEL);
		if (!adapter->msix_entries)
			return -ENOMEM;
	}

	for (vector = 0; vector < num_msix; vector++)
		adapter->msix_entries[vector].entry = vector;

restore:
	err = pci_enable_msix_exact(pdev, adapter->msix_entries, num_msix);
	if (err == -ENOSPC) {
		if (!adapter->drv_tss_rings && !adapter->drv_rss_rings)
			return err;

		netdev_info(adapter->netdev,
			    "Unable to allocate %d MSI-X vectors, Available vectors %d\n",
			    num_msix, err);

		num_msix = adapter->drv_tx_rings + adapter->drv_sds_rings;

		/* Set rings to 0 so we can restore original TSS/RSS count */
		adapter->drv_tss_rings = 0;
		adapter->drv_rss_rings = 0;

		if (qlcnic_83xx_check(adapter))
			num_msix += 1;

		netdev_info(adapter->netdev,
			    "Restoring %d Tx, %d SDS rings for total %d vectors.\n",
			    adapter->drv_tx_rings, adapter->drv_sds_rings,
			    num_msix);

		goto restore;
	} else if (err < 0) {
		return err;
	}

	adapter->ahw->num_msix = num_msix;
	if (adapter->drv_tss_rings > 0)
		adapter->drv_tx_rings = adapter->drv_tss_rings;

	if (adapter->drv_rss_rings > 0)
		adapter->drv_sds_rings = adapter->drv_rss_rings;

	return 0;
}