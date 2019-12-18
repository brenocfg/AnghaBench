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
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct lance_rx_desc {unsigned char rmd1_bits; int mblength; } ;
struct lance_regs {int rdp; } ;
struct lance_private {int rx_new; int rx_ring_mod_mask; struct lance_regs* ll; struct lance_init_block* init_block; } ;
struct lance_init_block {int /*<<< orphan*/ ** rx_buf; struct lance_rx_desc* brx_ring; } ;

/* Variables and functions */
 int LE_C0_INEA ; 
 int LE_C0_RINT ; 
 unsigned char LE_R1_BUF ; 
 unsigned char LE_R1_CRC ; 
 unsigned char LE_R1_EOP ; 
 unsigned char LE_R1_ERR ; 
 unsigned char LE_R1_FRA ; 
 unsigned char LE_R1_OFL ; 
 unsigned char LE_R1_OWN ; 
 unsigned char LE_R1_POK ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int lance_rx(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_init_block *ib = lp->init_block;
	volatile struct lance_regs *ll = lp->ll;
	volatile struct lance_rx_desc *rd;
	unsigned char bits;

#ifdef TEST_HITS
	int i;
	char buf[RX_RING_SIZE + 1];

	for (i = 0; i < RX_RING_SIZE; i++) {
		char r1_own = ib->brx_ring[i].rmd1_bits & LE_R1_OWN;
		if (i == lp->rx_new)
			buf[i] = r1_own ? '_' : 'X';
		else
			buf[i] = r1_own ? '.' : '1';
	}
	buf[RX_RING_SIZE] = 0;

	pr_debug("RxRing TestHits: [%s]\n", buf);
#endif

	ll->rdp = LE_C0_RINT | LE_C0_INEA;
	for (rd = &ib->brx_ring[lp->rx_new];
	     !((bits = rd->rmd1_bits) & LE_R1_OWN);
	     rd = &ib->brx_ring[lp->rx_new]) {

		/* We got an incomplete frame? */
		if ((bits & LE_R1_POK) != LE_R1_POK) {
			dev->stats.rx_over_errors++;
			dev->stats.rx_errors++;
			continue;
		} else if (bits & LE_R1_ERR) {
			/* Count only the end frame as a rx error,
			 * not the beginning
			 */
			if (bits & LE_R1_BUF)
				dev->stats.rx_fifo_errors++;
			if (bits & LE_R1_CRC)
				dev->stats.rx_crc_errors++;
			if (bits & LE_R1_OFL)
				dev->stats.rx_over_errors++;
			if (bits & LE_R1_FRA)
				dev->stats.rx_frame_errors++;
			if (bits & LE_R1_EOP)
				dev->stats.rx_errors++;
		} else {
			int len = (rd->mblength & 0xfff) - 4;
			struct sk_buff *skb = netdev_alloc_skb(dev, len + 2);

			if (!skb) {
				dev->stats.rx_dropped++;
				rd->mblength = 0;
				rd->rmd1_bits = LE_R1_OWN;
				lp->rx_new = (lp->rx_new + 1) & lp->rx_ring_mod_mask;
				return 0;
			}

			skb_reserve(skb, 2);		/* 16 byte align */
			skb_put(skb, len);		/* make room */
			skb_copy_to_linear_data(skb,
				 (unsigned char *)&ib->rx_buf[lp->rx_new][0],
				 len);
			skb->protocol = eth_type_trans(skb, dev);
			netif_rx(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += len;
		}

		/* Return the packet to the pool */
		rd->mblength = 0;
		rd->rmd1_bits = LE_R1_OWN;
		lp->rx_new = (lp->rx_new + 1) & lp->rx_ring_mod_mask;
	}
	return 0;
}