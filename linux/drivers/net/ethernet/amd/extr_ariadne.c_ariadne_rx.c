#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {short rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct ariadne_private {int cur_rx; TYPE_2__** rx_ring; scalar_t__* rx_buff; } ;
struct TYPE_4__ {int RMD1; int /*<<< orphan*/  RMD3; } ;

/* Variables and functions */
 int RF_BUFF ; 
 int RF_CRC ; 
 int RF_ENP ; 
 int RF_FRAM ; 
 int RF_OFLO ; 
 int RF_OWN ; 
 int RF_STP ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int lowb (int) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,short) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ariadne_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void const*,short) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 short swapw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ariadne_rx(struct net_device *dev)
{
	struct ariadne_private *priv = netdev_priv(dev);
	int entry = priv->cur_rx % RX_RING_SIZE;
	int i;

	/* If we own the next entry, it's a new packet. Send it up */
	while (!(lowb(priv->rx_ring[entry]->RMD1) & RF_OWN)) {
		int status = lowb(priv->rx_ring[entry]->RMD1);

		if (status != (RF_STP | RF_ENP)) {	/* There was an error */
			/* There is a tricky error noted by
			 * John Murphy <murf@perftech.com> to Russ Nelson:
			 * Even with full-sized buffers it's possible for a
			 * jabber packet to use two buffers, with only the
			 * last correctly noting the error
			 */
			/* Only count a general error at the end of a packet */
			if (status & RF_ENP)
				dev->stats.rx_errors++;
			if (status & RF_FRAM)
				dev->stats.rx_frame_errors++;
			if (status & RF_OFLO)
				dev->stats.rx_over_errors++;
			if (status & RF_CRC)
				dev->stats.rx_crc_errors++;
			if (status & RF_BUFF)
				dev->stats.rx_fifo_errors++;
			priv->rx_ring[entry]->RMD1 &= 0xff00 | RF_STP | RF_ENP;
		} else {
			/* Malloc up new buffer, compatible with net-3 */
			short pkt_len = swapw(priv->rx_ring[entry]->RMD3);
			struct sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 2);
			if (skb == NULL) {
				for (i = 0; i < RX_RING_SIZE; i++)
					if (lowb(priv->rx_ring[(entry + i) % RX_RING_SIZE]->RMD1) & RF_OWN)
						break;

				if (i > RX_RING_SIZE - 2) {
					dev->stats.rx_dropped++;
					priv->rx_ring[entry]->RMD1 |= RF_OWN;
					priv->cur_rx++;
				}
				break;
			}


			skb_reserve(skb, 2);	/* 16 byte align */
			skb_put(skb, pkt_len);	/* Make room */
			skb_copy_to_linear_data(skb,
						(const void *)priv->rx_buff[entry],
						pkt_len);
			skb->protocol = eth_type_trans(skb, dev);
			netdev_dbg(dev, "RX pkt type 0x%04x from %pM to %pM data %p len %u\n",
				   ((u_short *)skb->data)[6],
				   skb->data + 6, skb->data,
				   skb->data, skb->len);

			netif_rx(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		}

		priv->rx_ring[entry]->RMD1 |= RF_OWN;
		entry = (++priv->cur_rx) % RX_RING_SIZE;
	}

	priv->cur_rx = priv->cur_rx % RX_RING_SIZE;

	/* We should check that at least two ring entries are free.
	 * If not, we should free one and mark stats->rx_dropped++
	 */

	return 0;
}