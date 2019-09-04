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
typedef  int u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct cfspi {TYPE_2__* ndev; } ;
struct TYPE_4__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_CAIF ; 
 int PAD_POW2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 int cfspi_xmit (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (TYPE_2__*,int) ; 
 int netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int spi_down_head_align ; 
 int /*<<< orphan*/  spi_down_tail_align ; 
 int /*<<< orphan*/  spi_loop ; 

int cfspi_rxfrm(struct cfspi *cfspi, u8 *buf, size_t len)
{
	u8 *src = buf;

	caif_assert(buf != NULL);

	do {
		int res;
		struct sk_buff *skb = NULL;
		int spad = 0;
		int epad = 0;
		int pkt_len = 0;

		/*
		 * Compute head offset i.e. number of bytes added to
		 * get the start of the payload aligned.
		 */
		if (spi_down_head_align > 1) {
			spad = 1 + *src;
			src += spad;
		}

		/* Read length of CAIF frame (little endian). */
		pkt_len = *src;
		pkt_len |= ((*(src+1)) << 8) & 0xFF00;
		pkt_len += 2;	/* Add FCS fields. */

		/* Get a suitable caif packet and copy in data. */

		skb = netdev_alloc_skb(cfspi->ndev, pkt_len + 1);
		caif_assert(skb != NULL);

		skb_put_data(skb, src, pkt_len);
		src += pkt_len;

		skb->protocol = htons(ETH_P_CAIF);
		skb_reset_mac_header(skb);

		/*
		 * Push received packet up the stack.
		 */
		if (!spi_loop)
			res = netif_rx_ni(skb);
		else
			res = cfspi_xmit(skb, cfspi->ndev);

		if (!res) {
			cfspi->ndev->stats.rx_packets++;
			cfspi->ndev->stats.rx_bytes += pkt_len;
		} else
			cfspi->ndev->stats.rx_dropped++;

		/*
		 * Compute tail offset i.e. number of bytes added to
		 * get the complete CAIF frame aligned.
		 */
		epad = PAD_POW2((pkt_len + spad), spi_down_tail_align);
		src += epad;
	} while ((src - buf) < len);

	return src - buf;
}