#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct spider_net_hw_descr {int dmac_cmd_status; scalar_t__ data_status; scalar_t__ next_descr_addr; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_addr; } ;
struct spider_net_descr_chain {scalar_t__ head; int /*<<< orphan*/  lock; TYPE_2__* tail; } ;
struct spider_net_descr {scalar_t__ next; int /*<<< orphan*/  bus_addr; TYPE_4__* prev; struct sk_buff* skb; struct spider_net_hw_descr* hwdescr; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_iommu_map_error; } ;
struct spider_net_card {TYPE_5__* netdev; int /*<<< orphan*/  pdev; struct spider_net_descr_chain tx_chain; TYPE_1__ spider_stats; } ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_12__ {int protocol; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_3__* hwdescr; } ;
struct TYPE_9__ {int /*<<< orphan*/  next_descr_addr; } ;
struct TYPE_8__ {scalar_t__ prev; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int ENOMEM ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int SPIDER_NET_DESCR_CARDOWNED ; 
 int SPIDER_NET_DMAC_TCP ; 
 int SPIDER_NET_DMAC_TXFRMTL ; 
 int SPIDER_NET_DMAC_UDP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ netif_msg_tx_err (struct spider_net_card*) ; 
 int /*<<< orphan*/  netif_trans_update (TYPE_5__*) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
spider_net_prepare_tx_descr(struct spider_net_card *card,
			    struct sk_buff *skb)
{
	struct spider_net_descr_chain *chain = &card->tx_chain;
	struct spider_net_descr *descr;
	struct spider_net_hw_descr *hwdescr;
	dma_addr_t buf;
	unsigned long flags;

	buf = pci_map_single(card->pdev, skb->data, skb->len, PCI_DMA_TODEVICE);
	if (pci_dma_mapping_error(card->pdev, buf)) {
		if (netif_msg_tx_err(card) && net_ratelimit())
			dev_err(&card->netdev->dev, "could not iommu-map packet (%p, %i). "
				  "Dropping packet\n", skb->data, skb->len);
		card->spider_stats.tx_iommu_map_error++;
		return -ENOMEM;
	}

	spin_lock_irqsave(&chain->lock, flags);
	descr = card->tx_chain.head;
	if (descr->next == chain->tail->prev) {
		spin_unlock_irqrestore(&chain->lock, flags);
		pci_unmap_single(card->pdev, buf, skb->len, PCI_DMA_TODEVICE);
		return -ENOMEM;
	}
	hwdescr = descr->hwdescr;
	chain->head = descr->next;

	descr->skb = skb;
	hwdescr->buf_addr = buf;
	hwdescr->buf_size = skb->len;
	hwdescr->next_descr_addr = 0;
	hwdescr->data_status = 0;

	hwdescr->dmac_cmd_status =
			SPIDER_NET_DESCR_CARDOWNED | SPIDER_NET_DMAC_TXFRMTL;
	spin_unlock_irqrestore(&chain->lock, flags);

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		switch (ip_hdr(skb)->protocol) {
		case IPPROTO_TCP:
			hwdescr->dmac_cmd_status |= SPIDER_NET_DMAC_TCP;
			break;
		case IPPROTO_UDP:
			hwdescr->dmac_cmd_status |= SPIDER_NET_DMAC_UDP;
			break;
		}

	/* Chain the bus address, so that the DMA engine finds this descr. */
	wmb();
	descr->prev->hwdescr->next_descr_addr = descr->bus_addr;

	netif_trans_update(card->netdev); /* set netdev watchdog timer */
	return 0;
}