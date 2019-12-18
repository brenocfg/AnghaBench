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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct iwl_ssid_ie {int dummy; } ;
struct iwl_scan_umac_chan_param {int flags; int /*<<< orphan*/  count; } ;
struct iwl_scan_req_umac_tail_v2 {struct iwl_ssid_ie* direct_scan; int /*<<< orphan*/  preq; void* delay; TYPE_4__* schedule; } ;
struct iwl_scan_req_umac_tail_v1 {struct iwl_ssid_ie* direct_scan; int /*<<< orphan*/  preq; } ;
struct TYPE_7__ {int /*<<< orphan*/  general_flags2; void** num_of_fragments; } ;
struct iwl_scan_req_umac {void* flags; int /*<<< orphan*/  scan_start_mac_id; TYPE_3__ v8; void* general_flags; void* uid; } ;
struct iwl_scan_channel_cfg_umac {int dummy; } ;
struct iwl_mvm_vif {int /*<<< orphan*/  id; } ;
struct iwl_mvm_scan_params {int n_scan_plans; int delay; int /*<<< orphan*/  n_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  preq; struct cfg80211_sched_scan_plan* scan_plans; } ;
struct iwl_mvm {int* scan_uid_status; int /*<<< orphan*/  mutex; TYPE_2__* fw; struct iwl_scan_req_umac* scan_cmd; } ;
struct ieee80211_vif {int dummy; } ;
struct cfg80211_sched_scan_plan {int iterations; int interval; } ;
struct TYPE_8__ {int iter_count; void* interval; } ;
struct TYPE_5__ {int n_scan_channels; } ;
struct TYPE_6__ {TYPE_1__ ucode_capa; } ;

/* Variables and functions */
 int EINVAL ; 
 int IWL_MAX_SCHED_SCAN_PLANS ; 
 int IWL_MVM_SCAN_NETDETECT ; 
 int IWL_MVM_SCAN_SCHED ; 
 int IWL_SCAN_CHANNEL_FLAG_CACHE_ADD ; 
 int IWL_SCAN_CHANNEL_FLAG_EBS ; 
 int IWL_SCAN_CHANNEL_FLAG_EBS_ACCURATE ; 
 int IWL_SCAN_CHANNEL_FLAG_EBS_FRAG ; 
 void* IWL_SCAN_NUM_OF_FRAGS ; 
 int IWL_UMAC_SCAN_FLAG_PREEMPTIVE ; 
 int /*<<< orphan*/  IWL_UMAC_SCAN_GEN_FLAGS2_ALLOW_CHNL_REORDER ; 
 int IWL_UMAC_SCAN_GEN_FLAGS_FRAGMENTED ; 
 int IWL_UMAC_SCAN_GEN_FLAGS_LMAC2_FRAGMENTED ; 
 size_t SCAN_HB_LMAC_IDX ; 
 size_t SCAN_LB_LMAC_IDX ; 
 scalar_t__ WARN_ON (int) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 struct iwl_scan_umac_chan_param* iwl_mvm_get_scan_req_umac_channel (struct iwl_mvm*) ; 
 void* iwl_mvm_get_scan_req_umac_data (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_adaptive_dwell_v2_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_is_cdb_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_frag_ebs_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_scan_ext_chan_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_scan_set_legacy_probe_req (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iwl_mvm_scan_uid_by_status (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_scan_umac_dwell (struct iwl_mvm*,struct iwl_scan_req_umac*,struct iwl_mvm_scan_params*) ; 
 int iwl_mvm_scan_umac_flags (struct iwl_mvm*,struct iwl_mvm_scan_params*,struct ieee80211_vif*) ; 
 scalar_t__ iwl_mvm_scan_use_ebs (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_umac_scan_cfg_channels (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_scan_build_ssids (struct iwl_mvm_scan_params*,struct iwl_ssid_ie*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksize (struct iwl_scan_req_umac*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct iwl_scan_req_umac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_scan_umac(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			     struct iwl_mvm_scan_params *params,
			     int type)
{
	struct iwl_scan_req_umac *cmd = mvm->scan_cmd;
	struct iwl_scan_umac_chan_param *chan_param;
	void *cmd_data = iwl_mvm_get_scan_req_umac_data(mvm);
	void *sec_part = cmd_data + sizeof(struct iwl_scan_channel_cfg_umac) *
		mvm->fw->ucode_capa.n_scan_channels;
	struct iwl_scan_req_umac_tail_v2 *tail_v2 =
		(struct iwl_scan_req_umac_tail_v2 *)sec_part;
	struct iwl_scan_req_umac_tail_v1 *tail_v1;
	struct iwl_ssid_ie *direct_scan;
	int uid, i;
	u32 ssid_bitmap = 0;
	u8 channel_flags = 0;
	u16 gen_flags;
	struct iwl_mvm_vif *scan_vif = iwl_mvm_vif_from_mac80211(vif);

	chan_param = iwl_mvm_get_scan_req_umac_channel(mvm);

	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON(params->n_scan_plans > IWL_MAX_SCHED_SCAN_PLANS))
		return -EINVAL;

	uid = iwl_mvm_scan_uid_by_status(mvm, 0);
	if (uid < 0)
		return uid;

	memset(cmd, 0, ksize(cmd));

	iwl_mvm_scan_umac_dwell(mvm, cmd, params);

	mvm->scan_uid_status[uid] = type;

	cmd->uid = cpu_to_le32(uid);
	gen_flags = iwl_mvm_scan_umac_flags(mvm, params, vif);
	cmd->general_flags = cpu_to_le16(gen_flags);
	if (iwl_mvm_is_adaptive_dwell_v2_supported(mvm)) {
		if (gen_flags & IWL_UMAC_SCAN_GEN_FLAGS_FRAGMENTED)
			cmd->v8.num_of_fragments[SCAN_LB_LMAC_IDX] =
							IWL_SCAN_NUM_OF_FRAGS;
		if (gen_flags & IWL_UMAC_SCAN_GEN_FLAGS_LMAC2_FRAGMENTED)
			cmd->v8.num_of_fragments[SCAN_HB_LMAC_IDX] =
							IWL_SCAN_NUM_OF_FRAGS;

		cmd->v8.general_flags2 =
			IWL_UMAC_SCAN_GEN_FLAGS2_ALLOW_CHNL_REORDER;
	}

	cmd->scan_start_mac_id = scan_vif->id;

	if (type == IWL_MVM_SCAN_SCHED || type == IWL_MVM_SCAN_NETDETECT)
		cmd->flags = cpu_to_le32(IWL_UMAC_SCAN_FLAG_PREEMPTIVE);

	if (iwl_mvm_scan_use_ebs(mvm, vif)) {
		channel_flags = IWL_SCAN_CHANNEL_FLAG_EBS |
				IWL_SCAN_CHANNEL_FLAG_EBS_ACCURATE |
				IWL_SCAN_CHANNEL_FLAG_CACHE_ADD;

		/* set fragmented ebs for fragmented scan on HB channels */
		if (iwl_mvm_is_frag_ebs_supported(mvm)) {
			if (gen_flags &
			    IWL_UMAC_SCAN_GEN_FLAGS_LMAC2_FRAGMENTED ||
			    (!iwl_mvm_is_cdb_supported(mvm) &&
			     gen_flags & IWL_UMAC_SCAN_GEN_FLAGS_FRAGMENTED))
				channel_flags |= IWL_SCAN_CHANNEL_FLAG_EBS_FRAG;
		}
	}

	chan_param->flags = channel_flags;
	chan_param->count = params->n_channels;

	for (i = 0; i < params->n_scan_plans; i++) {
		struct cfg80211_sched_scan_plan *scan_plan =
			&params->scan_plans[i];

		tail_v2->schedule[i].iter_count = scan_plan->iterations;
		tail_v2->schedule[i].interval =
			cpu_to_le16(scan_plan->interval);
	}

	/*
	 * If the number of iterations of the last scan plan is set to
	 * zero, it should run infinitely. However, this is not always the case.
	 * For example, when regular scan is requested the driver sets one scan
	 * plan with one iteration.
	 */
	if (!tail_v2->schedule[i - 1].iter_count)
		tail_v2->schedule[i - 1].iter_count = 0xff;

	tail_v2->delay = cpu_to_le16(params->delay);

	if (iwl_mvm_is_scan_ext_chan_supported(mvm)) {
		tail_v2->preq = params->preq;
		direct_scan = tail_v2->direct_scan;
	} else {
		tail_v1 = (struct iwl_scan_req_umac_tail_v1 *)sec_part;
		iwl_mvm_scan_set_legacy_probe_req(&tail_v1->preq,
						  &params->preq);
		direct_scan = tail_v1->direct_scan;
	}
	iwl_scan_build_ssids(params, direct_scan, &ssid_bitmap);
	iwl_mvm_umac_scan_cfg_channels(mvm, params->channels,
				       params->n_channels, ssid_bitmap,
				       cmd_data);
	return 0;
}