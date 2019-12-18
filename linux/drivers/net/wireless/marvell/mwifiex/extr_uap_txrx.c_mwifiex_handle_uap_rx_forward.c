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
typedef  int /*<<< orphan*/  u8 ;
struct uap_rxpd {int /*<<< orphan*/  rx_pkt_offset; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_dest; } ;
struct rx_packet_hdr {TYPE_1__ eth803_hdr; } ;
struct mwifiex_private {int /*<<< orphan*/  media_connected; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/ *) ; 
 int mwifiex_process_rx_packet (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_uap_queue_bridged_pkt (struct mwifiex_private*,struct sk_buff*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 

int mwifiex_handle_uap_rx_forward(struct mwifiex_private *priv,
				  struct sk_buff *skb)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct uap_rxpd *uap_rx_pd;
	struct rx_packet_hdr *rx_pkt_hdr;
	u8 ra[ETH_ALEN];
	struct sk_buff *skb_uap;

	uap_rx_pd = (struct uap_rxpd *)(skb->data);
	rx_pkt_hdr = (void *)uap_rx_pd + le16_to_cpu(uap_rx_pd->rx_pkt_offset);

	/* don't do packet forwarding in disconnected state */
	if (!priv->media_connected) {
		mwifiex_dbg(adapter, ERROR,
			    "drop packet in disconnected state.\n");
		dev_kfree_skb_any(skb);
		return 0;
	}

	memcpy(ra, rx_pkt_hdr->eth803_hdr.h_dest, ETH_ALEN);

	if (is_multicast_ether_addr(ra)) {
		skb_uap = skb_copy(skb, GFP_ATOMIC);
		mwifiex_uap_queue_bridged_pkt(priv, skb_uap);
	} else {
		if (mwifiex_get_sta_entry(priv, ra)) {
			/* Requeue Intra-BSS packet */
			mwifiex_uap_queue_bridged_pkt(priv, skb);
			return 0;
		}
	}

	/* Forward unicat/Inter-BSS packets to kernel. */
	return mwifiex_process_rx_packet(priv, skb);
}