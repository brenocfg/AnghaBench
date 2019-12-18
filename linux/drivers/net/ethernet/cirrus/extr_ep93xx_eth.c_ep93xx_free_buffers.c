#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ep93xx_priv {TYPE_5__* descs; int /*<<< orphan*/  descs_dma_addr; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/ * rx_buf; TYPE_2__* dev; } ;
struct ep93xx_descs {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_10__ {TYPE_4__* tdesc; TYPE_3__* rdesc; } ;
struct TYPE_9__ {scalar_t__ buf_addr; } ;
struct TYPE_8__ {scalar_t__ buf_addr; } ;
struct TYPE_6__ {struct device* parent; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SIZE ; 
 int RX_QUEUE_ENTRIES ; 
 int TX_QUEUE_ENTRIES ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_free_buffers(struct ep93xx_priv *ep)
{
	struct device *dev = ep->dev->dev.parent;
	int i;

	if (!ep->descs)
		return;

	for (i = 0; i < RX_QUEUE_ENTRIES; i++) {
		dma_addr_t d;

		d = ep->descs->rdesc[i].buf_addr;
		if (d)
			dma_unmap_single(dev, d, PKT_BUF_SIZE, DMA_FROM_DEVICE);

		kfree(ep->rx_buf[i]);
	}

	for (i = 0; i < TX_QUEUE_ENTRIES; i++) {
		dma_addr_t d;

		d = ep->descs->tdesc[i].buf_addr;
		if (d)
			dma_unmap_single(dev, d, PKT_BUF_SIZE, DMA_TO_DEVICE);

		kfree(ep->tx_buf[i]);
	}

	dma_free_coherent(dev, sizeof(struct ep93xx_descs), ep->descs,
							ep->descs_dma_addr);
	ep->descs = NULL;
}