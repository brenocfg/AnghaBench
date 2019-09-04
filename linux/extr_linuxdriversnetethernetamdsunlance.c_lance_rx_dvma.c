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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct lance_rx_desc {int rmd1_bits; int mblength; } ;
struct lance_private {int rx_new; struct lance_init_block* init_block_mem; } ;
struct lance_init_block {int /*<<< orphan*/ ** rx_buf; struct lance_rx_desc* brx_ring; } ;

/* Variables and functions */
 int LE_R1_BUF ; 
 int LE_R1_CRC ; 
 int LE_R1_EOP ; 
 int LE_R1_ERR ; 
 int LE_R1_FRA ; 
 int LE_R1_OFL ; 
 int LE_R1_OWN ; 
 int LE_R1_POK ; 
 void* RX_NEXT (int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void lance_rx_dvma(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	struct lance_init_block *ib = lp->init_block_mem;
	struct lance_rx_desc *rd;
	u8 bits;
	int len, entry = lp->rx_new;
	struct sk_buff *skb;

	for (rd = &ib->brx_ring [entry];
	     !((bits = rd->rmd1_bits) & LE_R1_OWN);
	     rd = &ib->brx_ring [entry]) {

		/* We got an incomplete frame? */
		if ((bits & LE_R1_POK) != LE_R1_POK) {
			dev->stats.rx_over_errors++;
			dev->stats.rx_errors++;
		} else if (bits & LE_R1_ERR) {
			/* Count only the end frame as a rx error,
			 * not the beginning
			 */
			if (bits & LE_R1_BUF) dev->stats.rx_fifo_errors++;
			if (bits & LE_R1_CRC) dev->stats.rx_crc_errors++;
			if (bits & LE_R1_OFL) dev->stats.rx_over_errors++;
			if (bits & LE_R1_FRA) dev->stats.rx_frame_errors++;
			if (bits & LE_R1_EOP) dev->stats.rx_errors++;
		} else {
			len = (rd->mblength & 0xfff) - 4;
			skb = netdev_alloc_skb(dev, len + 2);

			if (skb == NULL) {
				dev->stats.rx_dropped++;
				rd->mblength = 0;
				rd->rmd1_bits = LE_R1_OWN;
				lp->rx_new = RX_NEXT(entry);
				return;
			}

			dev->stats.rx_bytes += len;

			skb_reserve(skb, 2);		/* 16 byte align */
			skb_put(skb, len);		/* make room */
			skb_copy_to_linear_data(skb,
					 (unsigned char *)&(ib->rx_buf [entry][0]),
					 len);
			skb->protocol = eth_type_trans(skb, dev);
			netif_rx(skb);
			dev->stats.rx_packets++;
		}

		/* Return the packet to the pool */
		rd->mblength = 0;
		rd->rmd1_bits = LE_R1_OWN;
		entry = RX_NEXT(entry);
	}

	lp->rx_new = entry;
}