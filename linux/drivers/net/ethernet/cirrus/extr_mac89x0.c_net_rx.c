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
struct sk_buff {int* data; int /*<<< orphan*/  protocol; } ;
struct net_local {int dummy; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; scalar_t__ mem_start; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PP_RxFrame ; 
 int /*<<< orphan*/  PP_RxLength ; 
 int /*<<< orphan*/  PP_RxStatus ; 
 int RX_CRC_ERROR ; 
 int RX_DRIBBLE ; 
 int RX_EXTRA_DATA ; 
 int RX_OK ; 
 int RX_RUNT ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct net_local*,int /*<<< orphan*/ ,struct net_device*,char*,int,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int readreg (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
net_rx(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	struct sk_buff *skb;
	int status, length;

	status = readreg(dev, PP_RxStatus);
	if ((status & RX_OK) == 0) {
		dev->stats.rx_errors++;
		if (status & RX_RUNT)
				dev->stats.rx_length_errors++;
		if (status & RX_EXTRA_DATA)
				dev->stats.rx_length_errors++;
		if ((status & RX_CRC_ERROR) &&
		    !(status & (RX_EXTRA_DATA|RX_RUNT)))
			/* per str 172 */
			dev->stats.rx_crc_errors++;
		if (status & RX_DRIBBLE)
				dev->stats.rx_frame_errors++;
		return;
	}

	length = readreg(dev, PP_RxLength);
	/* Malloc up new buffer. */
	skb = alloc_skb(length, GFP_ATOMIC);
	if (skb == NULL) {
		dev->stats.rx_dropped++;
		return;
	}
	skb_put(skb, length);

	skb_copy_to_linear_data(skb, (void *)(dev->mem_start + PP_RxFrame),
				length);

	netif_dbg(lp, rx_status, dev, "received %d byte packet of type %x\n",
		  length, skb->data[ETH_ALEN + ETH_ALEN] << 8 |
		  skb->data[ETH_ALEN + ETH_ALEN + 1]);

        skb->protocol=eth_type_trans(skb,dev);
	netif_rx(skb);
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += length;
}