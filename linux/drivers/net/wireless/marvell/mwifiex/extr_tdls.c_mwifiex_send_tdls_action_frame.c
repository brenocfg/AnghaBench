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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  tx_control ;
struct sk_buff {int len; int /*<<< orphan*/ * data; int /*<<< orphan*/  priority; } ;
struct mwifiex_txinfo {int /*<<< orphan*/  flags; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  bss_num; } ;
struct mwifiex_private {int /*<<< orphan*/  bss_type; int /*<<< orphan*/  bss_num; int /*<<< orphan*/  cfg_bssid; int /*<<< orphan*/  curr_addr; TYPE_1__* adapter; } ;
struct ieee_types_vht_oper {int dummy; } ;
struct ieee_types_vht_cap {int dummy; } ;
struct ieee_types_extcap {int dummy; } ;
struct ieee_types_bss_co_2040 {int dummy; } ;
struct ieee_types_aid {int dummy; } ;
struct ieee80211_tdls_lnkie {int dummy; } ;
struct ieee80211_tdls_data {int dummy; } ;
struct ieee80211_mgmt {int dummy; } ;
struct ieee80211_ht_operation {int dummy; } ;
struct ieee80211_ht_cap {int dummy; } ;
typedef  int /*<<< orphan*/  pkt_type ;
typedef  int /*<<< orphan*/  pkt_len ;
struct TYPE_2__ {scalar_t__ is_hw_11ac_capable; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MWIFIEX_BUF_FLAG_TDLS_PKT ; 
 int MWIFIEX_MGMT_FRAME_HEADER_SIZE ; 
 int MWIFIEX_MIN_DATA_HEADER_LEN ; 
 int /*<<< orphan*/  MWIFIEX_PRIO_VI ; 
 struct mwifiex_txinfo* MWIFIEX_SKB_TXCB (struct sk_buff*) ; 
 int MWIFIEX_SUPPORTED_RATES ; 
 int PKT_TYPE_MGMT ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (struct mwifiex_txinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mwifiex_construct_tdls_action_frame (struct mwifiex_private*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_queue_tx_pkt (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_tdls_add_link_ie (struct sk_buff*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

int mwifiex_send_tdls_action_frame(struct mwifiex_private *priv, const u8 *peer,
				   u8 action_code, u8 dialog_token,
				   u16 status_code, const u8 *extra_ies,
				   size_t extra_ies_len)
{
	struct sk_buff *skb;
	struct mwifiex_txinfo *tx_info;
	u8 *pos;
	u32 pkt_type, tx_control;
	u16 pkt_len, skb_len;

	skb_len = MWIFIEX_MIN_DATA_HEADER_LEN +
		  max(sizeof(struct ieee80211_mgmt),
		      sizeof(struct ieee80211_tdls_data)) +
		  MWIFIEX_MGMT_FRAME_HEADER_SIZE +
		  MWIFIEX_SUPPORTED_RATES +
		  sizeof(struct ieee_types_extcap) +
		  sizeof(struct ieee80211_ht_cap) +
		  sizeof(struct ieee_types_bss_co_2040) +
		  sizeof(struct ieee80211_ht_operation) +
		  sizeof(struct ieee80211_tdls_lnkie) +
		  extra_ies_len +
		  3 + /* Qos Info */
		  ETH_ALEN; /* Address4 */

	if (priv->adapter->is_hw_11ac_capable)
		skb_len += sizeof(struct ieee_types_vht_cap) +
			   sizeof(struct ieee_types_vht_oper) +
			   sizeof(struct ieee_types_aid);

	skb = dev_alloc_skb(skb_len);
	if (!skb) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "allocate skb failed for management frame\n");
		return -ENOMEM;
	}

	skb_reserve(skb, MWIFIEX_MIN_DATA_HEADER_LEN);

	pkt_type = PKT_TYPE_MGMT;
	tx_control = 0;
	pos = skb_put_zero(skb,
			   MWIFIEX_MGMT_FRAME_HEADER_SIZE + sizeof(pkt_len));
	memcpy(pos, &pkt_type, sizeof(pkt_type));
	memcpy(pos + sizeof(pkt_type), &tx_control, sizeof(tx_control));

	if (mwifiex_construct_tdls_action_frame(priv, peer, action_code,
						dialog_token, status_code,
						skb)) {
		dev_kfree_skb_any(skb);
		return -EINVAL;
	}

	if (extra_ies_len)
		skb_put_data(skb, extra_ies, extra_ies_len);

	/* the TDLS link IE is always added last we are the responder */

	mwifiex_tdls_add_link_ie(skb, peer, priv->curr_addr,
				 priv->cfg_bssid);

	skb->priority = MWIFIEX_PRIO_VI;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	memset(tx_info, 0, sizeof(*tx_info));
	tx_info->bss_num = priv->bss_num;
	tx_info->bss_type = priv->bss_type;
	tx_info->flags |= MWIFIEX_BUF_FLAG_TDLS_PKT;

	pkt_len = skb->len - MWIFIEX_MGMT_FRAME_HEADER_SIZE - sizeof(pkt_len);
	memcpy(skb->data + MWIFIEX_MGMT_FRAME_HEADER_SIZE, &pkt_len,
	       sizeof(pkt_len));
	__net_timestamp(skb);
	mwifiex_queue_tx_pkt(priv, skb);

	return 0;
}