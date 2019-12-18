#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tkip_cmd ;
struct wowlan_key_data {int configure_keys; int use_rsc_tsc; int use_tkip; struct iwl_wowlan_tkip_params_cmd* rsc_tsc; scalar_t__ error; struct iwl_wowlan_tkip_params_cmd* tkip; } ;
struct iwl_wowlan_tkip_params_cmd {int /*<<< orphan*/  replay_ctr; void* kek_len; int /*<<< orphan*/  kek; void* kck_len; int /*<<< orphan*/  kck; } ;
struct iwl_wowlan_kek_kck_material_cmd {int /*<<< orphan*/  replay_ctr; void* kek_len; int /*<<< orphan*/  kek; void* kck_len; int /*<<< orphan*/  kck; } ;
struct TYPE_4__ {int /*<<< orphan*/  replay_ctr; int /*<<< orphan*/  kek; int /*<<< orphan*/  kck; scalar_t__ valid; } ;
struct iwl_mvm_vif {TYPE_2__ rekey_data; } ;
struct iwl_mvm {TYPE_1__* fw; int /*<<< orphan*/  hw; } ;
struct ieee80211_vif {int dummy; } ;
typedef  int /*<<< orphan*/  kek_kck_cmd ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_TKIP_MIC_KEYS ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG ; 
 int /*<<< orphan*/  NL80211_KCK_LEN ; 
 int /*<<< orphan*/  NL80211_KEK_LEN ; 
 int /*<<< orphan*/  WOWLAN_KEK_KCK_MATERIAL ; 
 int /*<<< orphan*/  WOWLAN_TKIP_PARAM ; 
 int /*<<< orphan*/  WOWLAN_TSC_RSC_PARAM ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iter_keys (int /*<<< orphan*/ ,struct ieee80211_vif*,int /*<<< orphan*/ ,struct wowlan_key_data*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_wowlan_tkip_params_cmd*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_wowlan_program_keys ; 
 int /*<<< orphan*/  kfree (struct iwl_wowlan_tkip_params_cmd*) ; 
 struct iwl_wowlan_tkip_params_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwl_wowlan_tkip_params_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_mvm_wowlan_config_key_params(struct iwl_mvm *mvm,
					    struct ieee80211_vif *vif,
					    u32 cmd_flags)
{
	struct iwl_wowlan_kek_kck_material_cmd kek_kck_cmd = {};
	struct iwl_wowlan_tkip_params_cmd tkip_cmd = {};
	bool unified = fw_has_capa(&mvm->fw->ucode_capa,
				   IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);
	struct wowlan_key_data key_data = {
		.configure_keys = !unified,
		.use_rsc_tsc = false,
		.tkip = &tkip_cmd,
		.use_tkip = false,
	};
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	key_data.rsc_tsc = kzalloc(sizeof(*key_data.rsc_tsc), GFP_KERNEL);
	if (!key_data.rsc_tsc)
		return -ENOMEM;

	/*
	 * if we have to configure keys, call ieee80211_iter_keys(),
	 * as we need non-atomic context in order to take the
	 * required locks.
	 */
	/*
	 * Note that currently we don't propagate cmd_flags
	 * to the iterator. In case of key_data.configure_keys,
	 * all the configured commands are SYNC, and
	 * iwl_mvm_wowlan_program_keys() will take care of
	 * locking/unlocking mvm->mutex.
	 */
	ieee80211_iter_keys(mvm->hw, vif, iwl_mvm_wowlan_program_keys,
			    &key_data);

	if (key_data.error) {
		ret = -EIO;
		goto out;
	}

	if (key_data.use_rsc_tsc) {
		ret = iwl_mvm_send_cmd_pdu(mvm,
					   WOWLAN_TSC_RSC_PARAM, cmd_flags,
					   sizeof(*key_data.rsc_tsc),
					   key_data.rsc_tsc);
		if (ret)
			goto out;
	}

	if (key_data.use_tkip &&
	    !fw_has_api(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_API_TKIP_MIC_KEYS)) {
		ret = iwl_mvm_send_cmd_pdu(mvm,
					   WOWLAN_TKIP_PARAM,
					   cmd_flags, sizeof(tkip_cmd),
					   &tkip_cmd);
		if (ret)
			goto out;
	}

	/* configure rekey data only if offloaded rekey is supported (d3) */
	if (mvmvif->rekey_data.valid) {
		memset(&kek_kck_cmd, 0, sizeof(kek_kck_cmd));
		memcpy(kek_kck_cmd.kck, mvmvif->rekey_data.kck,
		       NL80211_KCK_LEN);
		kek_kck_cmd.kck_len = cpu_to_le16(NL80211_KCK_LEN);
		memcpy(kek_kck_cmd.kek, mvmvif->rekey_data.kek,
		       NL80211_KEK_LEN);
		kek_kck_cmd.kek_len = cpu_to_le16(NL80211_KEK_LEN);
		kek_kck_cmd.replay_ctr = mvmvif->rekey_data.replay_ctr;

		ret = iwl_mvm_send_cmd_pdu(mvm,
					   WOWLAN_KEK_KCK_MATERIAL, cmd_flags,
					   sizeof(kek_kck_cmd),
					   &kek_kck_cmd);
		if (ret)
			goto out;
	}
	ret = 0;
out:
	kfree(key_data.rsc_tsc);
	return ret;
}