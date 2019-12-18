#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  noa_attr; int /*<<< orphan*/  noa_active; } ;
struct iwl_probe_resp_data {scalar_t__ noa_len; TYPE_4__ notif; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  probe_resp_data; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vendor_ie {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  vif; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct TYPE_6__ {scalar_t__ variable; } ;
struct TYPE_7__ {TYPE_2__ probe_resp; } ;
struct ieee80211_mgmt {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int WLAN_OUI_TYPE_WFA_P2P ; 
 int WLAN_OUI_WFA ; 
 scalar_t__ cfg80211_find_ie_match (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int*,int,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct iwl_probe_resp_data* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int* skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static void iwl_mvm_probe_resp_set_noa(struct iwl_mvm *mvm,
				       struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct iwl_mvm_vif *mvmvif =
		iwl_mvm_vif_from_mac80211(info->control.vif);
	struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)skb->data;
	int base_len = (u8 *)mgmt->u.probe_resp.variable - (u8 *)mgmt;
	struct iwl_probe_resp_data *resp_data;
	u8 *ie, *pos;
	u8 match[] = {
		(WLAN_OUI_WFA >> 16) & 0xff,
		(WLAN_OUI_WFA >> 8) & 0xff,
		WLAN_OUI_WFA & 0xff,
		WLAN_OUI_TYPE_WFA_P2P,
	};

	rcu_read_lock();

	resp_data = rcu_dereference(mvmvif->probe_resp_data);
	if (!resp_data)
		goto out;

	if (!resp_data->notif.noa_active)
		goto out;

	ie = (u8 *)cfg80211_find_ie_match(WLAN_EID_VENDOR_SPECIFIC,
					  mgmt->u.probe_resp.variable,
					  skb->len - base_len,
					  match, 4, 2);
	if (!ie) {
		IWL_DEBUG_TX(mvm, "probe resp doesn't have P2P IE\n");
		goto out;
	}

	if (skb_tailroom(skb) < resp_data->noa_len) {
		if (pskb_expand_head(skb, 0, resp_data->noa_len, GFP_ATOMIC)) {
			IWL_ERR(mvm,
				"Failed to reallocate probe resp\n");
			goto out;
		}
	}

	pos = skb_put(skb, resp_data->noa_len);

	*pos++ = WLAN_EID_VENDOR_SPECIFIC;
	/* Set length of IE body (not including ID and length itself) */
	*pos++ = resp_data->noa_len - 2;
	*pos++ = (WLAN_OUI_WFA >> 16) & 0xff;
	*pos++ = (WLAN_OUI_WFA >> 8) & 0xff;
	*pos++ = WLAN_OUI_WFA & 0xff;
	*pos++ = WLAN_OUI_TYPE_WFA_P2P;

	memcpy(pos, &resp_data->notif.noa_attr,
	       resp_data->noa_len - sizeof(struct ieee80211_vendor_ie));

out:
	rcu_read_unlock();
}