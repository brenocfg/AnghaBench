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
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; } ;
struct atl1c_adapter {int /*<<< orphan*/ * rx_page; TYPE_1__* tpd_ring; TYPE_2__ ring_header; struct pci_dev* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * buffer_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atl1c_free_ring_resources(struct atl1c_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;

	pci_free_consistent(pdev, adapter->ring_header.size,
					adapter->ring_header.desc,
					adapter->ring_header.dma);
	adapter->ring_header.desc = NULL;

	/* Note: just free tdp_ring.buffer_info,
	*  it contain rfd_ring.buffer_info, do not double free */
	if (adapter->tpd_ring[0].buffer_info) {
		kfree(adapter->tpd_ring[0].buffer_info);
		adapter->tpd_ring[0].buffer_info = NULL;
	}
	if (adapter->rx_page) {
		put_page(adapter->rx_page);
		adapter->rx_page = NULL;
	}
}