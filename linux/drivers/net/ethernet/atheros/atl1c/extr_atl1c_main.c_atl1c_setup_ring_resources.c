#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct atl1c_tpd_ring {int count; int dma; int size; scalar_t__ buffer_info; int /*<<< orphan*/ * desc; } ;
struct atl1c_tpd_desc {int dummy; } ;
struct atl1c_rx_free_desc {int dummy; } ;
struct atl1c_rrd_ring {int count; int dma; int size; int /*<<< orphan*/ * desc; } ;
struct atl1c_ring_header {int size; int dma; scalar_t__ desc; } ;
struct atl1c_rfd_ring {int count; int dma; int size; int /*<<< orphan*/ * desc; scalar_t__ buffer_info; } ;
struct atl1c_recv_ret_status {int dummy; } ;
struct atl1c_buffer {int dummy; } ;
struct atl1c_adapter {struct atl1c_ring_header ring_header; struct atl1c_rrd_ring rrd_ring; struct atl1c_rfd_ring rfd_ring; struct atl1c_tpd_ring* tpd_ring; struct pci_dev* pdev; } ;

/* Variables and functions */
 int AT_MAX_TRANSMIT_QUEUE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int roundup (int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl1c_setup_ring_resources(struct atl1c_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	struct atl1c_tpd_ring *tpd_ring = adapter->tpd_ring;
	struct atl1c_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct atl1c_rrd_ring *rrd_ring = &adapter->rrd_ring;
	struct atl1c_ring_header *ring_header = &adapter->ring_header;
	int size;
	int i;
	int count = 0;
	int rx_desc_count = 0;
	u32 offset = 0;

	rrd_ring->count = rfd_ring->count;
	for (i = 1; i < AT_MAX_TRANSMIT_QUEUE; i++)
		tpd_ring[i].count = tpd_ring[0].count;

	/* 2 tpd queue, one high priority queue,
	 * another normal priority queue */
	size = sizeof(struct atl1c_buffer) * (tpd_ring->count * 2 +
		rfd_ring->count);
	tpd_ring->buffer_info = kzalloc(size, GFP_KERNEL);
	if (unlikely(!tpd_ring->buffer_info))
		goto err_nomem;

	for (i = 0; i < AT_MAX_TRANSMIT_QUEUE; i++) {
		tpd_ring[i].buffer_info =
			(tpd_ring->buffer_info + count);
		count += tpd_ring[i].count;
	}

	rfd_ring->buffer_info =
		(tpd_ring->buffer_info + count);
	count += rfd_ring->count;
	rx_desc_count += rfd_ring->count;

	/*
	 * real ring DMA buffer
	 * each ring/block may need up to 8 bytes for alignment, hence the
	 * additional bytes tacked onto the end.
	 */
	ring_header->size = size =
		sizeof(struct atl1c_tpd_desc) * tpd_ring->count * 2 +
		sizeof(struct atl1c_rx_free_desc) * rx_desc_count +
		sizeof(struct atl1c_recv_ret_status) * rx_desc_count +
		8 * 4;

	ring_header->desc = dma_alloc_coherent(&pdev->dev, ring_header->size,
					       &ring_header->dma, GFP_KERNEL);
	if (unlikely(!ring_header->desc)) {
		dev_err(&pdev->dev, "could not get memory for DMA buffer\n");
		goto err_nomem;
	}
	/* init TPD ring */

	tpd_ring[0].dma = roundup(ring_header->dma, 8);
	offset = tpd_ring[0].dma - ring_header->dma;
	for (i = 0; i < AT_MAX_TRANSMIT_QUEUE; i++) {
		tpd_ring[i].dma = ring_header->dma + offset;
		tpd_ring[i].desc = (u8 *) ring_header->desc + offset;
		tpd_ring[i].size =
			sizeof(struct atl1c_tpd_desc) * tpd_ring[i].count;
		offset += roundup(tpd_ring[i].size, 8);
	}
	/* init RFD ring */
	rfd_ring->dma = ring_header->dma + offset;
	rfd_ring->desc = (u8 *) ring_header->desc + offset;
	rfd_ring->size = sizeof(struct atl1c_rx_free_desc) * rfd_ring->count;
	offset += roundup(rfd_ring->size, 8);

	/* init RRD ring */
	rrd_ring->dma = ring_header->dma + offset;
	rrd_ring->desc = (u8 *) ring_header->desc + offset;
	rrd_ring->size = sizeof(struct atl1c_recv_ret_status) *
		rrd_ring->count;
	offset += roundup(rrd_ring->size, 8);

	return 0;

err_nomem:
	kfree(tpd_ring->buffer_info);
	return -ENOMEM;
}