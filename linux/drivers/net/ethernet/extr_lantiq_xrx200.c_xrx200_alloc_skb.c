#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t desc; TYPE_2__* desc_base; } ;
struct xrx200_chan {TYPE_3__ dma; TYPE_4__** skb; TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int ctl; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int LTQ_DMA_OWN ; 
 int LTQ_DMA_RX_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int XRX200_DMA_DATA_LEN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_4__*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xrx200_alloc_skb(struct xrx200_chan *ch)
{
	int ret = 0;

	ch->skb[ch->dma.desc] = netdev_alloc_skb_ip_align(ch->priv->net_dev,
							  XRX200_DMA_DATA_LEN);
	if (!ch->skb[ch->dma.desc]) {
		ret = -ENOMEM;
		goto skip;
	}

	ch->dma.desc_base[ch->dma.desc].addr = dma_map_single(ch->priv->dev,
			ch->skb[ch->dma.desc]->data, XRX200_DMA_DATA_LEN,
			DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(ch->priv->dev,
				       ch->dma.desc_base[ch->dma.desc].addr))) {
		dev_kfree_skb_any(ch->skb[ch->dma.desc]);
		ret = -ENOMEM;
		goto skip;
	}

skip:
	ch->dma.desc_base[ch->dma.desc].ctl =
		LTQ_DMA_OWN | LTQ_DMA_RX_OFFSET(NET_IP_ALIGN) |
		XRX200_DMA_DATA_LEN;

	return ret;
}