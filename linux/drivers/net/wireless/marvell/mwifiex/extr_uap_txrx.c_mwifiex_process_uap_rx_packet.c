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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct uap_rxpd {size_t priority; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  rx_pkt_type; int /*<<< orphan*/  rx_pkt_length; int /*<<< orphan*/  rx_pkt_offset; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_source; } ;
struct rx_packet_hdr {TYPE_1__ eth803_hdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_failed; } ;
struct mwifiex_sta_node {scalar_t__* rx_seq; TYPE_2__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_dropped; } ;
struct mwifiex_private {TYPE_3__ stats; int /*<<< orphan*/  ap_11n_enabled; int /*<<< orphan*/  sta_list_spinlock; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  ERROR ; 
 int ETH_ALEN ; 
 size_t MAX_NUM_TID ; 
 scalar_t__ PKT_TYPE_AMSDU ; 
 scalar_t__ PKT_TYPE_BAR ; 
 scalar_t__ PKT_TYPE_MGMT ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_11n_get_rx_reorder_tbl (struct mwifiex_private*,size_t,scalar_t__*) ; 
 int mwifiex_11n_rx_reorder_pkt (struct mwifiex_private*,scalar_t__,size_t,scalar_t__*,scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,scalar_t__*) ; 
 int mwifiex_handle_uap_rx_forward (struct mwifiex_private*,struct sk_buff*) ; 
 int mwifiex_process_mgmt_packet (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mwifiex_process_uap_rx_packet(struct mwifiex_private *priv,
				  struct sk_buff *skb)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	int ret;
	struct uap_rxpd *uap_rx_pd;
	struct rx_packet_hdr *rx_pkt_hdr;
	u16 rx_pkt_type;
	u8 ta[ETH_ALEN], pkt_type;
	struct mwifiex_sta_node *node;

	uap_rx_pd = (struct uap_rxpd *)(skb->data);
	rx_pkt_type = le16_to_cpu(uap_rx_pd->rx_pkt_type);
	rx_pkt_hdr = (void *)uap_rx_pd + le16_to_cpu(uap_rx_pd->rx_pkt_offset);

	ether_addr_copy(ta, rx_pkt_hdr->eth803_hdr.h_source);

	if ((le16_to_cpu(uap_rx_pd->rx_pkt_offset) +
	     le16_to_cpu(uap_rx_pd->rx_pkt_length)) > (u16) skb->len) {
		mwifiex_dbg(adapter, ERROR,
			    "wrong rx packet: len=%d, offset=%d, length=%d\n",
			    skb->len, le16_to_cpu(uap_rx_pd->rx_pkt_offset),
			    le16_to_cpu(uap_rx_pd->rx_pkt_length));
		priv->stats.rx_dropped++;

		node = mwifiex_get_sta_entry(priv, ta);
		if (node)
			node->stats.tx_failed++;

		dev_kfree_skb_any(skb);
		return 0;
	}

	if (rx_pkt_type == PKT_TYPE_MGMT) {
		ret = mwifiex_process_mgmt_packet(priv, skb);
		if (ret)
			mwifiex_dbg(adapter, DATA, "Rx of mgmt packet failed");
		dev_kfree_skb_any(skb);
		return ret;
	}


	if (rx_pkt_type != PKT_TYPE_BAR && uap_rx_pd->priority < MAX_NUM_TID) {
		spin_lock_bh(&priv->sta_list_spinlock);
		node = mwifiex_get_sta_entry(priv, ta);
		if (node)
			node->rx_seq[uap_rx_pd->priority] =
						le16_to_cpu(uap_rx_pd->seq_num);
		spin_unlock_bh(&priv->sta_list_spinlock);
	}

	if (!priv->ap_11n_enabled ||
	    (!mwifiex_11n_get_rx_reorder_tbl(priv, uap_rx_pd->priority, ta) &&
	    (le16_to_cpu(uap_rx_pd->rx_pkt_type) != PKT_TYPE_AMSDU))) {
		ret = mwifiex_handle_uap_rx_forward(priv, skb);
		return ret;
	}

	/* Reorder and send to kernel */
	pkt_type = (u8)le16_to_cpu(uap_rx_pd->rx_pkt_type);
	ret = mwifiex_11n_rx_reorder_pkt(priv, le16_to_cpu(uap_rx_pd->seq_num),
					 uap_rx_pd->priority, ta, pkt_type,
					 skb);

	if (ret || (rx_pkt_type == PKT_TYPE_BAR))
		dev_kfree_skb_any(skb);

	if (ret)
		priv->stats.rx_dropped++;

	return ret;
}