#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm {TYPE_3__* trans; TYPE_5__* fw; } ;
struct iwl_fw_dbg_trigger_txq_timer {int /*<<< orphan*/  p2p_device; int /*<<< orphan*/  p2p_go; int /*<<< orphan*/  p2p_client; int /*<<< orphan*/  softap; int /*<<< orphan*/  bss; int /*<<< orphan*/  ibss; int /*<<< orphan*/  command_queue; int /*<<< orphan*/  tdls; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct TYPE_11__ {int /*<<< orphan*/  ucode_capa; } ;
struct TYPE_10__ {scalar_t__ tfd_q_hang_detect; } ;
struct TYPE_9__ {TYPE_2__* trans_cfg; } ;
struct TYPE_8__ {TYPE_1__* base_params; } ;
struct TYPE_7__ {unsigned int wd_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_DBG_TRIGGER_TXQ_TIMERS ; 
 unsigned int IWL_DEF_WD_TIMEOUT ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_STA_PM_NOTIF ; 
 unsigned int IWL_WATCHDOG_DISABLED ; 
#define  NL80211_IFTYPE_ADHOC 134 
#define  NL80211_IFTYPE_AP 133 
#define  NL80211_IFTYPE_MONITOR 132 
#define  NL80211_IFTYPE_P2P_CLIENT 131 
#define  NL80211_IFTYPE_P2P_DEVICE 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ieee80211_vif_type_p2p (struct ieee80211_vif*) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_get_trigger (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_enabled (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_4__ iwlmvm_mod_params ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

unsigned int iwl_mvm_get_wd_timeout(struct iwl_mvm *mvm,
				    struct ieee80211_vif *vif,
				    bool tdls, bool cmd_q)
{
	struct iwl_fw_dbg_trigger_tlv *trigger;
	struct iwl_fw_dbg_trigger_txq_timer *txq_timer;
	unsigned int default_timeout = cmd_q ?
		IWL_DEF_WD_TIMEOUT :
		mvm->trans->trans_cfg->base_params->wd_timeout;

	if (!iwl_fw_dbg_trigger_enabled(mvm->fw, FW_DBG_TRIGGER_TXQ_TIMERS)) {
		/*
		 * We can't know when the station is asleep or awake, so we
		 * must disable the queue hang detection.
		 */
		if (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_STA_PM_NOTIF) &&
		    vif && vif->type == NL80211_IFTYPE_AP)
			return IWL_WATCHDOG_DISABLED;
		return iwlmvm_mod_params.tfd_q_hang_detect ?
			default_timeout : IWL_WATCHDOG_DISABLED;
	}

	trigger = iwl_fw_dbg_get_trigger(mvm->fw, FW_DBG_TRIGGER_TXQ_TIMERS);
	txq_timer = (void *)trigger->data;

	if (tdls)
		return le32_to_cpu(txq_timer->tdls);

	if (cmd_q)
		return le32_to_cpu(txq_timer->command_queue);

	if (WARN_ON(!vif))
		return default_timeout;

	switch (ieee80211_vif_type_p2p(vif)) {
	case NL80211_IFTYPE_ADHOC:
		return le32_to_cpu(txq_timer->ibss);
	case NL80211_IFTYPE_STATION:
		return le32_to_cpu(txq_timer->bss);
	case NL80211_IFTYPE_AP:
		return le32_to_cpu(txq_timer->softap);
	case NL80211_IFTYPE_P2P_CLIENT:
		return le32_to_cpu(txq_timer->p2p_client);
	case NL80211_IFTYPE_P2P_GO:
		return le32_to_cpu(txq_timer->p2p_go);
	case NL80211_IFTYPE_P2P_DEVICE:
		return le32_to_cpu(txq_timer->p2p_device);
	case NL80211_IFTYPE_MONITOR:
		return default_timeout;
	default:
		WARN_ON(1);
		return mvm->trans->trans_cfg->base_params->wd_timeout;
	}
}