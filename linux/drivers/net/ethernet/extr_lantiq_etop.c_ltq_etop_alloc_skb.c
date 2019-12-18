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
struct ltq_etop_priv {TYPE_1__* pdev; } ;
struct TYPE_8__ {size_t desc; TYPE_2__* desc_base; } ;
struct ltq_etop_chan {TYPE_3__ dma; TYPE_4__** skb; int /*<<< orphan*/  netdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int ctl; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPHYSADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int LTQ_DMA_OWN ; 
 int LTQ_DMA_RX_OFFSET (int /*<<< orphan*/ ) ; 
 int MAX_DMA_DATA_LEN ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* netdev_alloc_skb (int /*<<< orphan*/ ,int) ; 
 struct ltq_etop_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ltq_etop_alloc_skb(struct ltq_etop_chan *ch)
{
	struct ltq_etop_priv *priv = netdev_priv(ch->netdev);

	ch->skb[ch->dma.desc] = netdev_alloc_skb(ch->netdev, MAX_DMA_DATA_LEN);
	if (!ch->skb[ch->dma.desc])
		return -ENOMEM;
	ch->dma.desc_base[ch->dma.desc].addr = dma_map_single(&priv->pdev->dev,
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