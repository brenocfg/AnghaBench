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
struct ep93xx_priv {TYPE_5__* descs; void** tx_buf; void** rx_buf; int /*<<< orphan*/  descs_dma_addr; TYPE_2__* dev; } ;
struct ep93xx_descs {int dummy; } ;
struct device {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_10__ {TYPE_4__* tdesc; TYPE_3__* rdesc; } ;
struct TYPE_9__ {void* buf_addr; } ;
struct TYPE_8__ {int rdesc1; void* buf_addr; } ;
struct TYPE_6__ {struct device* parent; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PKT_BUF_SIZE ; 
 int RX_QUEUE_ENTRIES ; 
 int TX_QUEUE_ENTRIES ; 
 TYPE_5__* dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* dma_map_single (struct device*,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,void*) ; 
 int /*<<< orphan*/  ep93xx_free_buffers (struct ep93xx_priv*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xx_alloc_buffers(struct ep93xx_priv *ep)
{
	struct device *dev = ep->dev->dev.parent;
	int i;

	ep->descs = dma_alloc_coherent(dev, sizeof(struct ep93xx_descs),
				&ep->descs_dma_addr, GFP_KERNEL);
	if (ep->descs == NULL)
		return 1;

	for (i = 0; i < RX_QUEUE_ENTRIES; i++) {
		void *buf;
		dma_addr_t d;

		buf = kmalloc(PKT_BUF_SIZE, GFP_KERNEL);
		if (buf == NULL)
			goto err;

		d = dma_map_single(dev, buf, PKT_BUF_SIZE, DMA_FROM_DEVICE);
		if (dma_mapping_error(dev, d)) {
			kfree(buf);
			goto err;
		}

		ep->rx_buf[i] = buf;
		ep->descs->rdesc[i].buf_addr = d;
		ep->descs->rdesc[i].rdesc1 = (i << 16) | PKT_BUF_SIZE;
	}

	for (i = 0; i < TX_QUEUE_ENTRIES; i++) {
		void *buf;
		dma_addr_t d;

		buf = kmalloc(PKT_BUF_SIZE, GFP_KERNEL);
		if (buf == NULL)
			goto err;

		d = dma_map_single(dev, buf, PKT_BUF_SIZE, DMA_TO_DEVICE);
		if (dma_mapping_error(dev, d)) {
			kfree(buf);
			goto err;
		}

		ep->tx_buf[i] = buf;
		ep->descs->tdesc[i].buf_addr = d;
	}

	return 0;

err:
	ep93xx_free_buffers(ep);
	return 1;
}