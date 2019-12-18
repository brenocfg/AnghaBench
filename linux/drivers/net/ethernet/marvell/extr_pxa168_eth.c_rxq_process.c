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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct rx_desc {unsigned int cmd_sts; scalar_t__ byte_cnt; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_ptr; } ;
struct pxa168_eth_private {int rx_resource_err; int rx_curr_desc_q; int rx_used_desc_q; int rx_ring_size; TYPE_1__* pdev; int /*<<< orphan*/  rx_desc_count; struct sk_buff** rx_skb; struct rx_desc* p_rx_desc_area; } ;
struct net_device_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BUF_OWNED_BY_DMA ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int RX_ERROR ; 
 unsigned int RX_FIRST_DESC ; 
 unsigned int RX_LAST_DESC ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rxq_refill (struct net_device*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int rxq_process(struct net_device *dev, int budget)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	unsigned int received_packets = 0;
	struct sk_buff *skb;

	while (budget-- > 0) {
		int rx_next_curr_desc, rx_curr_desc, rx_used_desc;
		struct rx_desc *rx_desc;
		unsigned int cmd_sts;

		/* Do not process Rx ring in case of Rx ring resource error */
		if (pep->rx_resource_err)
			break;
		rx_curr_desc = pep->rx_curr_desc_q;
		rx_used_desc = pep->rx_used_desc_q;
		rx_desc = &pep->p_rx_desc_area[rx_curr_desc];
		cmd_sts = rx_desc->cmd_sts;
		dma_rmb();
		if (cmd_sts & (BUF_OWNED_BY_DMA))
			break;
		skb = pep->rx_skb[rx_curr_desc];
		pep->rx_skb[rx_curr_desc] = NULL;

		rx_next_curr_desc = (rx_curr_desc + 1) % pep->rx_ring_size;
		pep->rx_curr_desc_q = rx_next_curr_desc;

		/* Rx descriptors exhausted. */
		/* Set the Rx ring resource error flag */
		if (rx_next_curr_desc == rx_used_desc)
			pep->rx_resource_err = 1;
		pep->rx_desc_count--;
		dma_unmap_single(&pep->pdev->dev, rx_desc->buf_ptr,
				 rx_desc->buf_size,
				 DMA_FROM_DEVICE);
		received_packets++;
		/*
		 * Update statistics.
		 * Note byte count includes 4 byte CRC count
		 */
		stats->rx_packets++;
		stats->rx_bytes += rx_desc->byte_cnt;
		/*
		 * In case received a packet without first / last bits on OR
		 * the error summary bit is on, the packets needs to be droped.
		 */
		if (((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC)) !=
		     (RX_FIRST_DESC | RX_LAST_DESC))
		    || (cmd_sts & RX_ERROR)) {

			stats->rx_dropped++;
			if ((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC)) !=
			    (RX_FIRST_DESC | RX_LAST_DESC)) {
				if (net_ratelimit())
					netdev_err(dev,
						   "Rx pkt on multiple desc\n");
			}
			if (cmd_sts & RX_ERROR)
				stats->rx_errors++;
			dev_kfree_skb_irq(skb);
		} else {
			/*
			 * The -4 is for the CRC in the trailer of the
			 * received packet
			 */
			skb_put(skb, rx_desc->byte_cnt - 4);
			skb->protocol = eth_type_trans(skb, dev);
			netif_receive_skb(skb);
		}
	}
	/* Fill RX ring with skb's */
	rxq_refill(dev);
	return received_packets;
}