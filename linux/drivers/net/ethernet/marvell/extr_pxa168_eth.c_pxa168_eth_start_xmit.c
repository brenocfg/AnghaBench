#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tx_desc {int byte_cnt; int cmd_sts; int /*<<< orphan*/  buf_ptr; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct pxa168_eth_private {int tx_ring_size; int tx_desc_count; TYPE_1__* pdev; struct sk_buff** tx_skb; struct tx_desc* p_tx_desc_area; } ;
struct net_device_stats {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BUF_OWNED_BY_DMA ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  SDMA_CMD ; 
 int SDMA_CMD_ERD ; 
 int SDMA_CMD_TXDH ; 
 int TX_EN_INT ; 
 int TX_FIRST_DESC ; 
 int TX_GEN_CRC ; 
 int TX_LAST_DESC ; 
 int TX_ZERO_PADDING ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int eth_alloc_tx_desc_index (struct pxa168_eth_private*) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static netdev_tx_t
pxa168_eth_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	struct tx_desc *desc;
	int tx_index;
	int length;

	tx_index = eth_alloc_tx_desc_index(pep);
	desc = &pep->p_tx_desc_area[tx_index];
	length = skb->len;
	pep->tx_skb[tx_index] = skb;
	desc->byte_cnt = length;
	desc->buf_ptr = dma_map_single(&pep->pdev->dev, skb->data, length,
					DMA_TO_DEVICE);

	skb_tx_timestamp(skb);

	dma_wmb();
	desc->cmd_sts = BUF_OWNED_BY_DMA | TX_GEN_CRC | TX_FIRST_DESC |
			TX_ZERO_PADDING | TX_LAST_DESC | TX_EN_INT;
	wmb();
	wrl(pep, SDMA_CMD, SDMA_CMD_TXDH | SDMA_CMD_ERD);

	stats->tx_bytes += length;
	stats->tx_packets++;
	netif_trans_update(dev);
	if (pep->tx_ring_size - pep->tx_desc_count <= 1) {
		/* We handled the current skb, but now we are out of space.*/
		netif_stop_queue(dev);
	}

	return NETDEV_TX_OK;
}