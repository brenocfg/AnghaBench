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
struct sk_buff {scalar_t__ len; scalar_t__ truesize; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct mwifiex_txinfo {int /*<<< orphan*/  flags; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  bss_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  last_rx; } ;
struct mwifiex_sta_node {TYPE_1__ stats; } ;
struct mwifiex_private {int /*<<< orphan*/  netdev; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  bss_num; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {scalar_t__ iface_type; int /*<<< orphan*/  pending_bridged_pkts; int /*<<< orphan*/  tx_pending; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MWIFIEX_BRIDGED_PKTS_THR_HIGH ; 
 int /*<<< orphan*/  MWIFIEX_BUF_FLAG_BRIDGED_PKT ; 
 scalar_t__ MWIFIEX_MIN_DATA_HEADER_LEN ; 
 scalar_t__ MWIFIEX_PCIE ; 
 scalar_t__ MWIFIEX_RX_DATA_BUF_SIZE ; 
 struct mwifiex_txinfo* MWIFIEX_SKB_TXCB (struct sk_buff*) ; 
 scalar_t__ MWIFIEX_USB ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct mwifiex_txinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_queue_main_work (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_uap_cleanup_tx_queues (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_wmm_add_buf_txqueue (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,scalar_t__) ; 

int mwifiex_uap_recv_packet(struct mwifiex_private *priv,
			    struct sk_buff *skb)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_sta_node *src_node;
	struct ethhdr *p_ethhdr;
	struct sk_buff *skb_uap;
	struct mwifiex_txinfo *tx_info;

	if (!skb)
		return -1;

	p_ethhdr = (void *)skb->data;
	src_node = mwifiex_get_sta_entry(priv, p_ethhdr->h_source);
	if (src_node) {
		src_node->stats.last_rx = jiffies;
		src_node->stats.rx_bytes += skb->len;
		src_node->stats.rx_packets++;
	}

	if (is_multicast_ether_addr(p_ethhdr->h_dest) ||
	    mwifiex_get_sta_entry(priv, p_ethhdr->h_dest)) {
		if (skb_headroom(skb) < MWIFIEX_MIN_DATA_HEADER_LEN)
			skb_uap =
			skb_realloc_headroom(skb, MWIFIEX_MIN_DATA_HEADER_LEN);
		else
			skb_uap = skb_copy(skb, GFP_ATOMIC);

		if (likely(skb_uap)) {
			tx_info = MWIFIEX_SKB_TXCB(skb_uap);
			memset(tx_info, 0, sizeof(*tx_info));
			tx_info->bss_num = priv->bss_num;
			tx_info->bss_type = priv->bss_type;
			tx_info->flags |= MWIFIEX_BUF_FLAG_BRIDGED_PKT;
			__net_timestamp(skb_uap);
			mwifiex_wmm_add_buf_txqueue(priv, skb_uap);
			atomic_inc(&adapter->tx_pending);
			atomic_inc(&adapter->pending_bridged_pkts);
			if ((atomic_read(&adapter->pending_bridged_pkts) >=
					MWIFIEX_BRIDGED_PKTS_THR_HIGH)) {
				mwifiex_dbg(adapter, ERROR,
					    "Tx: Bridge packet limit reached. Drop packet!\n");
				mwifiex_uap_cleanup_tx_queues(priv);
			}

		} else {
			mwifiex_dbg(adapter, ERROR, "failed to allocate skb_uap");
		}

		mwifiex_queue_main_work(adapter);
		/* Don't forward Intra-BSS unicast packet to upper layer*/
		if (mwifiex_get_sta_entry(priv, p_ethhdr->h_dest))
			return 0;
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
	if ((adapter->iface_type == MWIFIEX_USB ||
	     adapter->iface_type == MWIFIEX_PCIE) &&
	    skb->truesize > MWIFIEX_RX_DATA_BUF_SIZE)
		skb->truesize += (skb->len - MWIFIEX_RX_DATA_BUF_SIZE);

	/* Forward multicast/broadcast packet to upper layer*/
	if (in_interrupt())
		netif_rx(skb);
	else
		netif_rx_ni(skb);

	return 0;
}