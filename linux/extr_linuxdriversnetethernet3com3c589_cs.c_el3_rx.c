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
struct TYPE_2__ {short rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ EL3_STATUS ; 
 scalar_t__ RX_FIFO ; 
 scalar_t__ RX_STATUS ; 
 int /*<<< orphan*/  RxDiscard ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  insl (scalar_t__,int /*<<< orphan*/ ,short) ; 
 short inw (scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,short) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,short,...) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  tc589_wait_for_completion (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int el3_rx(struct net_device *dev)
{
	unsigned int ioaddr = dev->base_addr;
	int worklimit = 32;
	short rx_status;

	netdev_dbg(dev, "in rx_packet(), status %4.4x, rx_status %4.4x.\n",
	       inw(ioaddr+EL3_STATUS), inw(ioaddr+RX_STATUS));
	while (!((rx_status = inw(ioaddr + RX_STATUS)) & 0x8000) &&
		    worklimit > 0) {
		worklimit--;
		if (rx_status & 0x4000) { /* Error, update stats. */
			short error = rx_status & 0x3800;
			dev->stats.rx_errors++;
			switch (error) {
			case 0x0000:
				dev->stats.rx_over_errors++;
				break;
			case 0x0800:
				dev->stats.rx_length_errors++;
				break;
			case 0x1000:
				dev->stats.rx_frame_errors++;
				break;
			case 0x1800:
				dev->stats.rx_length_errors++;
				break;
			case 0x2000:
				dev->stats.rx_frame_errors++;
				break;
			case 0x2800:
				dev->stats.rx_crc_errors++;
				break;
			}
		} else {
			short pkt_len = rx_status & 0x7ff;
			struct sk_buff *skb;

			skb = netdev_alloc_skb(dev, pkt_len + 5);

			netdev_dbg(dev, "    Receiving packet size %d status %4.4x.\n",
		       pkt_len, rx_status);
			if (skb != NULL) {
				skb_reserve(skb, 2);
				insl(ioaddr+RX_FIFO, skb_put(skb, pkt_len),
			(pkt_len+3)>>2);
				skb->protocol = eth_type_trans(skb, dev);
				netif_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
			} else {
				netdev_dbg(dev, "couldn't allocate a sk_buff of size %d.\n",
			   pkt_len);
				dev->stats.rx_dropped++;
			}
		}
		/* Pop the top of the Rx FIFO */
		tc589_wait_for_completion(dev, RxDiscard);
	}
	if (worklimit == 0)
		netdev_warn(dev, "too much work in el3_rx!\n");
	return 0;
}