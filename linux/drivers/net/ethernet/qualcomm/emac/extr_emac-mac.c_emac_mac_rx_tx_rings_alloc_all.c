#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct emac_ring_header {unsigned int size; scalar_t__ used; scalar_t__ dma_addr; int /*<<< orphan*/ * v_addr; } ;
struct TYPE_9__ {unsigned int count; } ;
struct TYPE_14__ {TYPE_2__ tpd; } ;
struct TYPE_11__ {unsigned int count; } ;
struct TYPE_10__ {unsigned int count; } ;
struct TYPE_12__ {TYPE_4__ rfd; TYPE_3__ rrd; } ;
struct emac_adapter {unsigned int tx_desc_cnt; unsigned int rx_desc_cnt; int tpd_size; int rfd_size; int rrd_size; TYPE_6__* netdev; TYPE_7__ tx_q; TYPE_5__ rx_q; struct emac_ring_header ring_header; } ;
struct device {int dummy; } ;
struct TYPE_8__ {struct device* parent; } ;
struct TYPE_13__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * dma_alloc_coherent (struct device*,unsigned int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,unsigned int,int /*<<< orphan*/ *,scalar_t__) ; 
 int emac_rx_descs_alloc (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_tx_q_bufs_free (struct emac_adapter*) ; 
 int emac_tx_q_desc_alloc (struct emac_adapter*,TYPE_7__*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_6__*,char*) ; 

int emac_mac_rx_tx_rings_alloc_all(struct emac_adapter *adpt)
{
	struct emac_ring_header *ring_header = &adpt->ring_header;
	struct device *dev = adpt->netdev->dev.parent;
	unsigned int num_tx_descs = adpt->tx_desc_cnt;
	unsigned int num_rx_descs = adpt->rx_desc_cnt;
	int ret;

	adpt->tx_q.tpd.count = adpt->tx_desc_cnt;

	adpt->rx_q.rrd.count = adpt->rx_desc_cnt;
	adpt->rx_q.rfd.count = adpt->rx_desc_cnt;

	/* Ring DMA buffer. Each ring may need up to 8 bytes for alignment,
	 * hence the additional padding bytes are allocated.
	 */
	ring_header->size = num_tx_descs * (adpt->tpd_size * 4) +
			    num_rx_descs * (adpt->rfd_size * 4) +
			    num_rx_descs * (adpt->rrd_size * 4) +
			    8 + 2 * 8; /* 8 byte per one Tx and two Rx rings */

	ring_header->used = 0;
	ring_header->v_addr = dma_alloc_coherent(dev, ring_header->size,
						 &ring_header->dma_addr,
						 GFP_KERNEL);
	if (!ring_header->v_addr)
		return -ENOMEM;

	ring_header->used = ALIGN(ring_header->dma_addr, 8) -
							ring_header->dma_addr;

	ret = emac_tx_q_desc_alloc(adpt, &adpt->tx_q);
	if (ret) {
		netdev_err(adpt->netdev, "error: Tx Queue alloc failed\n");
		goto err_alloc_tx;
	}

	ret = emac_rx_descs_alloc(adpt);
	if (ret) {
		netdev_err(adpt->netdev, "error: Rx Queue alloc failed\n");
		goto err_alloc_rx;
	}

	return 0;

err_alloc_rx:
	emac_tx_q_bufs_free(adpt);
err_alloc_tx:
	dma_free_coherent(dev, ring_header->size,
			  ring_header->v_addr, ring_header->dma_addr);

	ring_header->v_addr   = NULL;
	ring_header->dma_addr = 0;
	ring_header->size     = 0;
	ring_header->used     = 0;

	return ret;
}