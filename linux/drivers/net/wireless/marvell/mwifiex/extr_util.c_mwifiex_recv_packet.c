#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; scalar_t__ truesize; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  last_rx; } ;
struct mwifiex_sta_node {TYPE_2__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct mwifiex_private {TYPE_3__* adapter; int /*<<< orphan*/  netdev; TYPE_1__ stats; } ;
struct ethhdr {int /*<<< orphan*/  h_source; } ;
struct TYPE_6__ {scalar_t__ iface_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 scalar_t__ GET_BSS_ROLE (struct mwifiex_private*) ; 
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 scalar_t__ MWIFIEX_PCIE ; 
 scalar_t__ MWIFIEX_RX_DATA_BUF_SIZE ; 
 scalar_t__ MWIFIEX_USB ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  jiffies ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 

int mwifiex_recv_packet(struct mwifiex_private *priv, struct sk_buff *skb)
{
	struct mwifiex_sta_node *src_node;
	struct ethhdr *p_ethhdr;

	if (!skb)
		return -1;

	priv->stats.rx_bytes += skb->len;
	priv->stats.rx_packets++;

	if (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) {
		p_ethhdr = (void *)skb->data;
		src_node = mwifiex_get_sta_entry(priv, p_ethhdr->h_source);
		if (src_node) {
			src_node->stats.last_rx = jiffies;
			src_node->stats.rx_bytes += skb->len;
			src_node->stats.rx_packets++;
		}
	}

	skb->dev = priv->netdev;
	skb->protocol = eth_type_trans(skb, priv->netdev);
	skb->ip_summed = CHECKSUM_NONE;

	/* This is required only in case of 11n and USB/PCIE as we alloc
	 * a buffer of 4K only if its 11N (to be able to receive 4K
	 * AMSDU packets). In case of SD we allocate buffers based
	 * on the size of packet and hence this is not needed.
	 *
	 * Modifying the truesize here as our allocation for each
	 * skb is 4K but we only receive 2K packets and this cause
	 * the kernel to start dropping packets in case where
	 * application has allocated buffer based on 2K size i.e.
	 * if there a 64K packet received (in IP fragments and
	 * application allocates 64K to receive this packet but
	 * this packet would almost double up because we allocate
	 * each 1.5K fragment in 4K and pass it up. As soon as the
	 * 64K limit hits kernel will start to drop rest of the
	 * fragments. Currently we fail the Filesndl-ht.scr script
	 * for UDP, hence this fix
	 */
	if ((priv->adapter->iface_type == MWIFIEX_USB ||
	     priv->adapter->iface_type == MWIFIEX_PCIE) &&
	    (skb->truesize > MWIFIEX_RX_DATA_BUF_SIZE))
		skb->truesize += (skb->len - MWIFIEX_RX_DATA_BUF_SIZE);

	if (in_interrupt())
		netif_rx(skb);
	else
		netif_rx_ni(skb);

	return 0;
}