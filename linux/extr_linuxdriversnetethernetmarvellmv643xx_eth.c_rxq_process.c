#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct rx_queue {size_t rx_curr_desc; size_t rx_ring_size; int index; scalar_t__ rx_desc_count; struct sk_buff** rx_skb; struct rx_desc* rx_desc_area; } ;
struct rx_desc {unsigned int cmd_sts; int byte_cnt; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_ptr; } ;
struct net_device_stats {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct mv643xx_eth_private {int work_rx_refill; int work_rx; TYPE_2__* dev; int /*<<< orphan*/  napi; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; struct net_device_stats stats; } ;

/* Variables and functions */
 unsigned int BUFFER_OWNED_BY_DMA ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int ERROR_SUMMARY ; 
 unsigned int LAYER_4_CHECKSUM_OK ; 
 unsigned int RX_FIRST_DESC ; 
 unsigned int RX_LAST_DESC ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  rmb () ; 
 struct mv643xx_eth_private* rxq_to_mp (struct rx_queue*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int rxq_process(struct rx_queue *rxq, int budget)
{
	struct mv643xx_eth_private *mp = rxq_to_mp(rxq);
	struct net_device_stats *stats = &mp->dev->stats;
	int rx;

	rx = 0;
	while (rx < budget && rxq->rx_desc_count) {
		struct rx_desc *rx_desc;
		unsigned int cmd_sts;
		struct sk_buff *skb;
		u16 byte_cnt;

		rx_desc = &rxq->rx_desc_area[rxq->rx_curr_desc];

		cmd_sts = rx_desc->cmd_sts;
		if (cmd_sts & BUFFER_OWNED_BY_DMA)
			break;
		rmb();

		skb = rxq->rx_skb[rxq->rx_curr_desc];
		rxq->rx_skb[rxq->rx_curr_desc] = NULL;

		rxq->rx_curr_desc++;
		if (rxq->rx_curr_desc == rxq->rx_ring_size)
			rxq->rx_curr_desc = 0;

		dma_unmap_single(mp->dev->dev.parent, rx_desc->buf_ptr,
				 rx_desc->buf_size, DMA_FROM_DEVICE);
		rxq->rx_desc_count--;
		rx++;

		mp->work_rx_refill |= 1 << rxq->index;

		byte_cnt = rx_desc->byte_cnt;

		/*
		 * Update statistics.
		 *
		 * Note that the descriptor byte count includes 2 dummy
		 * bytes automatically inserted by the hardware at the
		 * start of the packet (which we don't count), and a 4
		 * byte CRC at the end of the packet (which we do count).
		 */
		stats->rx_packets++;
		stats->rx_bytes += byte_cnt - 2;

		/*
		 * In case we received a packet without first / last bits
		 * on, or the error summary bit is set, the packet needs
		 * to be dropped.
		 */
		if ((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC | ERROR_SUMMARY))
			!= (RX_FIRST_DESC | RX_LAST_DESC))
			goto err;

		/*
		 * The -4 is for the CRC in the trailer of the
		 * received packet
		 */
		skb_put(skb, byte_cnt - 2 - 4);

		if (cmd_sts & LAYER_4_CHECKSUM_OK)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->protocol = eth_type_trans(skb, mp->dev);

		napi_gro_receive(&mp->napi, skb);

		continue;

err:
		stats->rx_dropped++;

		if ((cmd_sts & (RX_FIRST_DESC | RX_LAST_DESC)) !=
			(RX_FIRST_DESC | RX_LAST_DESC)) {
			if (net_ratelimit())
				netdev_err(mp->dev,
					   "received packet spanning multiple descriptors\n");
		}

		if (cmd_sts & ERROR_SUMMARY)
			stats->rx_errors++;

		dev_kfree_skb(skb);
	}

	if (rx < budget)
		mp->work_rx &= ~(1 << rxq->index);

	return rx;
}