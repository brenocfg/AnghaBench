#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm {int /*<<< orphan*/  fwrt; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct iwl_fw_dbg_trigger_tdls {int action_bitmap; int /*<<< orphan*/  peer; scalar_t__ peer_mode; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum nl80211_tdls_operation { ____Placeholder_nl80211_tdls_operation } nl80211_tdls_operation ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_TDLS ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*,char*,int /*<<< orphan*/ *,int) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_trigger_on (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwl_mvm_tdls_check_trigger(struct iwl_mvm *mvm,
			   struct ieee80211_vif *vif, u8 *peer_addr,
			   enum nl80211_tdls_operation action)
{
	struct iwl_fw_dbg_trigger_tlv *trig;
	struct iwl_fw_dbg_trigger_tdls *tdls_trig;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vif_to_wdev(vif),
				     FW_DBG_TRIGGER_TDLS);
	if (!trig)
		return;

	tdls_trig = (void *)trig->data;

	if (!(tdls_trig->action_bitmap & BIT(action)))
		return;

	if (tdls_trig->peer_mode &&
	    memcmp(tdls_trig->peer, peer_addr, ETH_ALEN) != 0)
		return;

	iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
				"TDLS event occurred, peer %pM, action %d",
				peer_addr, action);
}