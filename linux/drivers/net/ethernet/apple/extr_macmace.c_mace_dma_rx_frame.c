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
struct TYPE_2__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct mace_frame {unsigned int rcvsts; unsigned int rcvcnt; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned int RS_CLSN ; 
 unsigned int RS_FCSERR ; 
 unsigned int RS_FRAMERR ; 
 unsigned int RS_OFLO ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void mace_dma_rx_frame(struct net_device *dev, struct mace_frame *mf)
{
	struct sk_buff *skb;
	unsigned int frame_status = mf->rcvsts;

	if (frame_status & (RS_OFLO | RS_CLSN | RS_FRAMERR | RS_FCSERR)) {
		dev->stats.rx_errors++;
		if (frame_status & RS_OFLO)
			dev->stats.rx_fifo_errors++;
		if (frame_status & RS_CLSN)
			dev->stats.collisions++;
		if (frame_status & RS_FRAMERR)
			dev->stats.rx_frame_errors++;
		if (frame_status & RS_FCSERR)
			dev->stats.rx_crc_errors++;
	} else {
		unsigned int frame_length = mf->rcvcnt + ((frame_status & 0x0F) << 8 );

		skb = netdev_alloc_skb(dev, frame_length + 2);
		if (!skb) {
			dev->stats.rx_dropped++;
			return;
		}
		skb_reserve(skb, 2);
		skb_put_data(skb, mf->data, frame_length);

		skb->protocol = eth_type_trans(skb, dev);
		netif_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += frame_length;
	}
}