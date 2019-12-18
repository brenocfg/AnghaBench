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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct rxpd {int /*<<< orphan*/  rx_pkt_length; int /*<<< orphan*/  rx_pkt_offset; int /*<<< orphan*/  rx_pkt_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  h_proto; } ;
struct rx_packet_hdr {TYPE_2__ eth803_hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  iftype; } ;
struct mwifiex_private {scalar_t__ bss_role; TYPE_3__* adapter; TYPE_1__ wdev; int /*<<< orphan*/  curr_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  fw_cap_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ ETH_P_TDLS ; 
 scalar_t__ ISSUPP_TDLS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 scalar_t__ PKT_TYPE_AMSDU ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  ieee80211_amsdu_to_8023s (struct sk_buff*,struct sk_buff_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_process_tdls_action_frame (struct mwifiex_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mwifiex_recv_packet (struct mwifiex_private*,struct sk_buff*) ; 
 int mwifiex_uap_recv_packet (struct mwifiex_private*,struct sk_buff*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int mwifiex_11n_dispatch_amsdu_pkt(struct mwifiex_private *priv,
					  struct sk_buff *skb)
{
	struct rxpd *local_rx_pd = (struct rxpd *)(skb->data);
	int ret;

	if (le16_to_cpu(local_rx_pd->rx_pkt_type) == PKT_TYPE_AMSDU) {
		struct sk_buff_head list;
		struct sk_buff *rx_skb;

		__skb_queue_head_init(&list);

		skb_pull(skb, le16_to_cpu(local_rx_pd->rx_pkt_offset));
		skb_trim(skb, le16_to_cpu(local_rx_pd->rx_pkt_length));

		ieee80211_amsdu_to_8023s(skb, &list, priv->curr_addr,
					 priv->wdev.iftype, 0, NULL, NULL);

		while (!skb_queue_empty(&list)) {
			struct rx_packet_hdr *rx_hdr;

			rx_skb = __skb_dequeue(&list);
			rx_hdr = (struct rx_packet_hdr *)rx_skb->data;
			if (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
			    ntohs(rx_hdr->eth803_hdr.h_proto) == ETH_P_TDLS) {
				mwifiex_process_tdls_action_frame(priv,
								  (u8 *)rx_hdr,
								  skb->len);
			}

			if (priv->bss_role == MWIFIEX_BSS_ROLE_UAP)
				ret = mwifiex_uap_recv_packet(priv, rx_skb);
			else
				ret = mwifiex_recv_packet(priv, rx_skb);
			if (ret == -1)
				mwifiex_dbg(priv->adapter, ERROR,
					    "Rx of A-MSDU failed");
		}
		return 0;
	}

	return -1;
}