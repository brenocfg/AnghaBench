#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t desc; TYPE_1__* desc_base; } ;
struct ltq_etop_chan {TYPE_2__ dma; TYPE_3__** skb; int /*<<< orphan*/  netdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int ctl; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPHYSADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int LTQ_DMA_OWN ; 
 int LTQ_DMA_RX_OFFSET (int /*<<< orphan*/ ) ; 
 int MAX_DMA_DATA_LEN ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* netdev_alloc_skb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ltq_etop_alloc_skb(struct ltq_etop_chan *ch)
{
	ch->skb[ch->dma.desc] = netdev_alloc_skb(ch->netdev, MAX_DMA_DATA_LEN);
	if (!ch->skb[ch->dma.desc])
		return -ENOMEM;
	ch->dma.desc_base[ch->dma.desc].addr = dma_map_single(NULL,
		ch->skb[ch->dma.desc]->data, MAX_DMA_DATA_LEN,
		DMA_FROM_DEVICE);
	ch->dma.desc_base[ch->dma.desc].addr =
		CPHYSADDR(ch->skb[ch->dma.desc]->data);
	ch->dma.desc_base[ch->dma.desc].ctl =
		LTQ_DMA_OWN | LTQ_DMA_RX_OFFSET(NET_IP_ALIGN) |
		MAX_DMA_DATA_LEN;
	skb_reserve(ch->skb[ch->dma.desc], NET_IP_ALIGN);
	return 0;
}