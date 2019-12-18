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
typedef  int u8 ;
struct tx_packet_desc {int dummy; } ;
struct stats_msg_block {int dummy; } ;
struct rx_return_desc {int dummy; } ;
struct rx_free_desc {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct coals_msg_block {int dummy; } ;
struct atl1_tpd_ring {int count; int dma; int* desc; int size; scalar_t__ buffer_info; } ;
struct atl1_rrd_ring {int count; int dma; int* desc; int size; } ;
struct atl1_ring_header {int size; int dma; scalar_t__ desc; } ;
struct atl1_rfd_ring {int count; int dma; int* desc; int size; scalar_t__ buffer_info; } ;
struct atl1_buffer {int dummy; } ;
struct TYPE_4__ {int dma; struct coals_msg_block* cmb; } ;
struct TYPE_3__ {int dma; struct stats_msg_block* smb; } ;
struct atl1_adapter {TYPE_2__ cmb; TYPE_1__ smb; struct pci_dev* pdev; struct atl1_ring_header ring_header; struct atl1_rrd_ring rrd_ring; struct atl1_rfd_ring rfd_ring; struct atl1_tpd_ring tpd_ring; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_drv (struct atl1_adapter*) ; 
 scalar_t__ pci_alloc_consistent (struct pci_dev*,int,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static s32 atl1_setup_ring_resources(struct atl1_adapter *adapter)
{
	struct atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	struct atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;
	struct atl1_ring_header *ring_header = &adapter->ring_header;
	struct pci_dev *pdev = adapter->pdev;
	int size;
	u8 offset = 0;

	size = sizeof(struct atl1_buffer) * (tpd_ring->count + rfd_ring->count);
	tpd_ring->buffer_info = kzalloc(size, GFP_KERNEL);
	if (unlikely(!tpd_ring->buffer_info)) {
		if (netif_msg_drv(adapter))
			dev_err(&pdev->dev, "kzalloc failed , size = D%d\n",
				size);
		goto err_nomem;
	}
	rfd_ring->buffer_info =
		(tpd_ring->buffer_info + tpd_ring->count);

	/*
	 * real ring DMA buffer
	 * each ring/block may need up to 8 bytes for alignment, hence the
	 * additional 40 bytes tacked onto the end.
	 */
	ring_header->size = size =
		sizeof(struct tx_packet_desc) * tpd_ring->count
		+ sizeof(struct rx_free_desc) * rfd_ring->count
		+ sizeof(struct rx_return_desc) * rrd_ring->count
		+ sizeof(struct coals_msg_block)
		+ sizeof(struct stats_msg_block)
		+ 40;

	ring_header->desc = pci_alloc_consistent(pdev, ring_header->size,
		&ring_header->dma);
	if (unlikely(!ring_header->desc)) {
		if (netif_msg_drv(adapter))
			dev_err(&pdev->dev, "pci_alloc_consistent failed\n");
		goto err_nomem;
	}

	/* init TPD ring */
	tpd_ring->dma = ring_header->dma;
	offset = (tpd_ring->dma & 0x7) ? (8 - (ring_header->dma & 0x7)) : 0;
	tpd_ring->dma += offset;
	tpd_ring->desc = (u8 *) ring_header->desc + offset;
	tpd_ring->size = sizeof(struct tx_packet_desc) * tpd_ring->count;

	/* init RFD ring */
	rfd_ring->dma = tpd_ring->dma + tpd_ring->size;
	offset = (rfd_ring->dma & 0x7) ? (8 - (rfd_ring->dma & 0x7)) : 0;
	rfd_ring->dma += offset;
	rfd_ring->desc = (u8 *) tpd_ring->desc + (tpd_ring->size + offset);
	rfd_ring->size = sizeof(struct rx_free_desc) * rfd_ring->count;


	/* init RRD ring */
	rrd_ring->dma = rfd_ring->dma + rfd_ring->size;
	offset = (rrd_ring->dma & 0x7) ? (8 - (rrd_ring->dma & 0x7)) : 0;
	rrd_ring->dma += offset;
	rrd_ring->desc = (u8 *) rfd_ring->desc + (rfd_ring->size + offset);
	rrd_ring->size = sizeof(struct rx_return_desc) * rrd_ring->count;


	/* init CMB */
	adapter->cmb.dma = rrd_ring->dma + rrd_ring->size;
	offset = (adapter->cmb.dma & 0x7) ? (8 - (adapter->cmb.dma & 0x7)) : 0;
	adapter->cmb.dma += offset;
	adapter->cmb.cmb = (struct coals_msg_block *)
		((u8 *) rrd_ring->desc + (rrd_ring->size + offset));

	/* init SMB */
	adapter->smb.dma = adapter->cmb.dma + sizeof(struct coals_msg_block);
	offset = (adapter->smb.dma & 0x7) ? (8 - (adapter->smb.dma & 0x7)) : 0;
	adapter->smb.dma += offset;
	adapter->smb.smb = (struct stats_msg_block *)
		((u8 *) adapter->cmb.cmb +
		(sizeof(struct coals_msg_block) + offset));

	return 0;

err_nomem:
	kfree(tpd_ring->buffer_info);
	return -ENOMEM;
}