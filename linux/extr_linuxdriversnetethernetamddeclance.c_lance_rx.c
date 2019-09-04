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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; scalar_t__ mem_start; } ;
struct lance_private {size_t rx_new; int* rx_buf_ptr_lnc; int /*<<< orphan*/  type; int /*<<< orphan*/ * rx_buf_ptr_cpu; } ;

/* Variables and functions */
 unsigned short LE_R1_BUF ; 
 unsigned short LE_R1_CRC ; 
 unsigned short LE_R1_EOP ; 
 unsigned short LE_R1_ERR ; 
 unsigned short LE_R1_FRA ; 
 unsigned short LE_R1_OFL ; 
 unsigned short LE_R1_OWN ; 
 unsigned short LE_R1_POK ; 
 int RX_BUFF_SIZE ; 
 int RX_RING_MOD_MASK ; 
 int /*<<< orphan*/ * brx_ring ; 
 int /*<<< orphan*/  cp_from_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  length ; 
 int /*<<< orphan*/ * lib_ptr (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mblength ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int* rds_ptr (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmd1 ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int lance_rx(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile u16 *ib = (volatile u16 *)dev->mem_start;
	volatile u16 *rd;
	unsigned short bits;
	int entry, len;
	struct sk_buff *skb;

#ifdef TEST_HITS
	{
		int i;

		printk("[");
		for (i = 0; i < RX_RING_SIZE; i++) {
			if (i == lp->rx_new)
				printk("%s", *lib_ptr(ib, brx_ring[i].rmd1,
						      lp->type) &
					     LE_R1_OWN ? "_" : "X");
			else
				printk("%s", *lib_ptr(ib, brx_ring[i].rmd1,
						      lp->type) &
					     LE_R1_OWN ? "." : "1");
		}
		printk("]");
	}
#endif

	for (rd = lib_ptr(ib, brx_ring[lp->rx_new], lp->type);
	     !((bits = *rds_ptr(rd, rmd1, lp->type)) & LE_R1_OWN);
	     rd = lib_ptr(ib, brx_ring[lp->rx_new], lp->type)) {
		entry = lp->rx_new;

		/* We got an incomplete frame? */
		if ((bits & LE_R1_POK) != LE_R1_POK) {
			dev->stats.rx_over_errors++;
			dev->stats.rx_errors++;
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
			len = (*rds_ptr(rd, mblength, lp->type) & 0xfff) - 4;
			skb = netdev_alloc_skb(dev, len + 2);

			if (skb == 0) {
				dev->stats.rx_dropped++;
				*rds_ptr(rd, mblength, lp->type) = 0;
				*rds_ptr(rd, rmd1, lp->type) =
					((lp->rx_buf_ptr_lnc[entry] >> 16) &
					 0xff) | LE_R1_OWN;
				lp->rx_new = (entry + 1) & RX_RING_MOD_MASK;
				return 0;
			}
			dev->stats.rx_bytes += len;

			skb_reserve(skb, 2);	/* 16 byte align */
			skb_put(skb, len);	/* make room */

			cp_from_buf(lp->type, skb->data,
				    lp->rx_buf_ptr_cpu[entry], len);

			skb->protocol = eth_type_trans(skb, dev);
			netif_rx(skb);
			dev->stats.rx_packets++;
		}

		/* Return the packet to the pool */
		*rds_ptr(rd, mblength, lp->type) = 0;
		*rds_ptr(rd, length, lp->type) = -RX_BUFF_SIZE | 0xf000;
		*rds_ptr(rd, rmd1, lp->type) =
			((lp->rx_buf_ptr_lnc[entry] >> 16) & 0xff) | LE_R1_OWN;
		lp->rx_new = (entry + 1) & RX_RING_MOD_MASK;
	}
	return 0;
}