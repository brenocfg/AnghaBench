#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct TYPE_10__ {int /*<<< orphan*/  rx_agg_state; } ;
struct rtl_tid_data {TYPE_5__ agg; } ;
struct rtl_sta_info {struct rtl_tid_data* tids; } ;
struct rtl_priv {int dummy; } ;
struct rtl_mac {int /*<<< orphan*/  act_scanning; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  capab; } ;
struct TYPE_7__ {TYPE_1__ addba_req; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr3; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
#define  ACT_ADDBAREQ 131 
#define  ACT_ADDBARSP 130 
#define  ACT_CAT_BA 129 
#define  ACT_DELBA 128 
 int /*<<< orphan*/  COMP_INIT ; 
 int COMP_RECV ; 
 int COMP_SEND ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int IEEE80211_ADDBA_PARAM_TID_MASK ; 
 int MAC80211_3ADDR_LEN ; 
 int MAX_TID_COUNT ; 
 int /*<<< orphan*/  RTL_RX_AGG_START ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ieee80211_is_action (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_agg_start (struct ieee80211_hw*,struct ieee80211_hdr*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct ieee80211_sta* rtl_find_sta (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 
 struct ieee80211_hdr* rtl_get_hdr (struct sk_buff*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool rtl_action_proc(struct ieee80211_hw *hw, struct sk_buff *skb, u8 is_tx)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct ieee80211_hdr *hdr = rtl_get_hdr(skb);
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	__le16 fc = rtl_get_fc(skb);
	u8 *act = (u8 *)(((u8 *)skb->data + MAC80211_3ADDR_LEN));
	u8 category;

	if (!ieee80211_is_action(fc))
		return true;

	category = *act;
	act++;
	switch (category) {
	case ACT_CAT_BA:
		switch (*act) {
		case ACT_ADDBAREQ:
			if (mac->act_scanning)
				return false;

			RT_TRACE(rtlpriv, (COMP_SEND | COMP_RECV), DBG_DMESG,
				"%s ACT_ADDBAREQ From :%pM\n",
				is_tx ? "Tx" : "Rx", hdr->addr2);
			RT_PRINT_DATA(rtlpriv, COMP_INIT, DBG_DMESG, "req\n",
				skb->data, skb->len);
			if (!is_tx) {
				struct ieee80211_sta *sta = NULL;
				struct rtl_sta_info *sta_entry = NULL;
				struct rtl_tid_data *tid_data;
				struct ieee80211_mgmt *mgmt = (void *)skb->data;
				u16 capab = 0, tid = 0;

				rcu_read_lock();
				sta = rtl_find_sta(hw, hdr->addr3);
				if (sta == NULL) {
					RT_TRACE(rtlpriv, COMP_SEND | COMP_RECV,
						 DBG_DMESG, "sta is NULL\n");
					rcu_read_unlock();
					return true;
				}

				sta_entry =
					(struct rtl_sta_info *)sta->drv_priv;
				if (!sta_entry) {
					rcu_read_unlock();
					return true;
				}
				capab =
				  le16_to_cpu(mgmt->u.action.u.addba_req.capab);
				tid = (capab &
				       IEEE80211_ADDBA_PARAM_TID_MASK) >> 2;
				if (tid >= MAX_TID_COUNT) {
					rcu_read_unlock();
					return true;
				}
				tid_data = &sta_entry->tids[tid];
				if (tid_data->agg.rx_agg_state ==
				    RTL_RX_AGG_START)
					process_agg_start(hw, hdr, tid);
				rcu_read_unlock();
			}
			break;
		case ACT_ADDBARSP:
			RT_TRACE(rtlpriv, (COMP_SEND | COMP_RECV), DBG_DMESG,
				 "%s ACT_ADDBARSP From :%pM\n",
				  is_tx ? "Tx" : "Rx", hdr->addr2);
			break;
		case ACT_DELBA:
			RT_TRACE(rtlpriv, (COMP_SEND | COMP_RECV), DBG_DMESG,
				 "ACT_ADDBADEL From :%pM\n", hdr->addr2);
			break;
		}
		break;
	default:
		break;
	}

	return true;
}