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
struct atl1_tpd_ring {scalar_t__ dma; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * buffer_info; } ;
struct atl1_rrd_ring {scalar_t__ dma; int /*<<< orphan*/ * desc; } ;
struct atl1_ring_header {int /*<<< orphan*/  dma; int /*<<< orphan*/  desc; int /*<<< orphan*/  size; } ;
struct atl1_rfd_ring {scalar_t__ dma; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * buffer_info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * smb; scalar_t__ dma; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cmb; scalar_t__ dma; } ;
struct atl1_adapter {TYPE_2__ smb; TYPE_1__ cmb; struct atl1_ring_header ring_header; struct atl1_rrd_ring rrd_ring; struct atl1_rfd_ring rfd_ring; struct atl1_tpd_ring tpd_ring; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1_clean_rx_ring (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_clean_tx_ring (struct atl1_adapter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1_free_ring_resources(struct atl1_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	struct atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	struct atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;
	struct atl1_ring_header *ring_header = &adapter->ring_header;

	atl1_clean_tx_ring(adapter);
	atl1_clean_rx_ring(adapter);

	kfree(tpd_ring->buffer_info);
	pci_free_consistent(pdev, ring_header->size, ring_header->desc,
		ring_header->dma);

	tpd_ring->buffer_info = NULL;
	tpd_ring->desc = NULL;
	tpd_ring->dma = 0;

	rfd_ring->buffer_info = NULL;
	rfd_ring->desc = NULL;
	rfd_ring->dma = 0;

	rrd_ring->desc = NULL;
	rrd_ring->dma = 0;

	adapter->cmb.dma = 0;
	adapter->cmb.cmb = NULL;

	adapter->smb.dma = 0;
	adapter->smb.smb = NULL;
}