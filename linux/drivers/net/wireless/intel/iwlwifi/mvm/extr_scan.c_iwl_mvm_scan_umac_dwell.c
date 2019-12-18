#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct TYPE_12__ {void* suspend_time; void* max_out_time; void* scan_priority; void* fragmented_dwell; void* passive_dwell; void* active_dwell; void* extended_dwell; } ;
struct TYPE_11__ {void** suspend_time; void** max_out_time; void* scan_priority; } ;
struct TYPE_10__ {void** passive_dwell; void** active_dwell; } ;
struct TYPE_9__ {void* fragmented_dwell; void* passive_dwell; void* active_dwell; void** suspend_time; void** max_out_time; void* scan_priority; void* adwell_max_budget; int /*<<< orphan*/  adwell_default_n_aps; int /*<<< orphan*/  adwell_default_n_aps_social; } ;
struct TYPE_7__ {int /*<<< orphan*/  adwell_default_hb_n_aps; } ;
struct iwl_scan_req_umac {void* ooc_priority; TYPE_6__ v1; TYPE_5__ v6; TYPE_4__ v8; TYPE_3__ v7; TYPE_1__ v9; } ;
struct iwl_mvm_scan_timing_params {int /*<<< orphan*/  suspend_time; int /*<<< orphan*/  max_out_time; } ;
struct iwl_mvm_scan_params {size_t type; size_t hb_type; void* measurement_dwell; TYPE_2__* ssids; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_8__ {scalar_t__ ssid_len; } ;

/* Variables and functions */
 scalar_t__ IWL_MVM_ADWELL_MAX_BUDGET ; 
 int /*<<< orphan*/  IWL_SCAN_ADWELL_DEFAULT_HB_N_APS ; 
 int /*<<< orphan*/  IWL_SCAN_ADWELL_DEFAULT_LB_N_APS ; 
 int /*<<< orphan*/  IWL_SCAN_ADWELL_DEFAULT_N_APS_SOCIAL ; 
 scalar_t__ IWL_SCAN_ADWELL_MAX_BUDGET_DIRECTED_SCAN ; 
 scalar_t__ IWL_SCAN_ADWELL_MAX_BUDGET_FULL_SCAN ; 
 void* IWL_SCAN_DWELL_ACTIVE ; 
 void* IWL_SCAN_DWELL_EXTENDED ; 
 void* IWL_SCAN_DWELL_FRAGMENTED ; 
 void* IWL_SCAN_DWELL_PASSIVE ; 
 int /*<<< orphan*/  IWL_SCAN_PRIORITY_EXT_2 ; 
 int /*<<< orphan*/  IWL_SCAN_PRIORITY_EXT_6 ; 
 size_t SCAN_HB_LMAC_IDX ; 
 size_t SCAN_LB_LMAC_IDX ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_cdb_scan_api (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_adaptive_dwell_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_is_adaptive_dwell_v2_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_adwell_hb_ap_num_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_cdb_supported (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_regular_scan (struct iwl_mvm_scan_params*) ; 
 struct iwl_mvm_scan_timing_params* scan_timing ; 

__attribute__((used)) static void iwl_mvm_scan_umac_dwell(struct iwl_mvm *mvm,
				    struct iwl_scan_req_umac *cmd,
				    struct iwl_mvm_scan_params *params)
{
	struct iwl_mvm_scan_timing_params *timing, *hb_timing;
	u8 active_dwell, passive_dwell;

	timing = &scan_timing[params->type];
	active_dwell = params->measurement_dwell ?
		params->measurement_dwell : IWL_SCAN_DWELL_ACTIVE;
	passive_dwell = params->measurement_dwell ?
		params->measurement_dwell : IWL_SCAN_DWELL_PASSIVE;

	if (iwl_mvm_is_adaptive_dwell_supported(mvm)) {
		cmd->v7.adwell_default_n_aps_social =
			IWL_SCAN_ADWELL_DEFAULT_N_APS_SOCIAL;
		cmd->v7.adwell_default_n_aps =
			IWL_SCAN_ADWELL_DEFAULT_LB_N_APS;

		if (iwl_mvm_is_adwell_hb_ap_num_supported(mvm))
			cmd->v9.adwell_default_hb_n_aps =
				IWL_SCAN_ADWELL_DEFAULT_HB_N_APS;

		/* if custom max budget was configured with debugfs */
		if (IWL_MVM_ADWELL_MAX_BUDGET)
			cmd->v7.adwell_max_budget =
				cpu_to_le16(IWL_MVM_ADWELL_MAX_BUDGET);
		else if (params->ssids && params->ssids[0].ssid_len)
			cmd->v7.adwell_max_budget =
				cpu_to_le16(IWL_SCAN_ADWELL_MAX_BUDGET_DIRECTED_SCAN);
		else
			cmd->v7.adwell_max_budget =
				cpu_to_le16(IWL_SCAN_ADWELL_MAX_BUDGET_FULL_SCAN);

		cmd->v7.scan_priority = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
		cmd->v7.max_out_time[SCAN_LB_LMAC_IDX] =
			cpu_to_le32(timing->max_out_time);
		cmd->v7.suspend_time[SCAN_LB_LMAC_IDX] =
			cpu_to_le32(timing->suspend_time);

		if (iwl_mvm_is_cdb_supported(mvm)) {
			hb_timing = &scan_timing[params->hb_type];

			cmd->v7.max_out_time[SCAN_HB_LMAC_IDX] =
				cpu_to_le32(hb_timing->max_out_time);
			cmd->v7.suspend_time[SCAN_HB_LMAC_IDX] =
				cpu_to_le32(hb_timing->suspend_time);
		}

		if (!iwl_mvm_is_adaptive_dwell_v2_supported(mvm)) {
			cmd->v7.active_dwell = active_dwell;
			cmd->v7.passive_dwell = passive_dwell;
			cmd->v7.fragmented_dwell = IWL_SCAN_DWELL_FRAGMENTED;
		} else {
			cmd->v8.active_dwell[SCAN_LB_LMAC_IDX] = active_dwell;
			cmd->v8.passive_dwell[SCAN_LB_LMAC_IDX] = passive_dwell;
			if (iwl_mvm_is_cdb_supported(mvm)) {
				cmd->v8.active_dwell[SCAN_HB_LMAC_IDX] =
					active_dwell;
				cmd->v8.passive_dwell[SCAN_HB_LMAC_IDX] =
					passive_dwell;
			}
		}
	} else {
		cmd->v1.extended_dwell = params->measurement_dwell ?
			params->measurement_dwell : IWL_SCAN_DWELL_EXTENDED;
		cmd->v1.active_dwell = active_dwell;
		cmd->v1.passive_dwell = passive_dwell;
		cmd->v1.fragmented_dwell = IWL_SCAN_DWELL_FRAGMENTED;

		if (iwl_mvm_is_cdb_supported(mvm)) {
			hb_timing = &scan_timing[params->hb_type];

			cmd->v6.max_out_time[SCAN_HB_LMAC_IDX] =
					cpu_to_le32(hb_timing->max_out_time);
			cmd->v6.suspend_time[SCAN_HB_LMAC_IDX] =
					cpu_to_le32(hb_timing->suspend_time);
		}

		if (iwl_mvm_cdb_scan_api(mvm)) {
			cmd->v6.scan_priority =
				cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
			cmd->v6.max_out_time[SCAN_LB_LMAC_IDX] =
				cpu_to_le32(timing->max_out_time);
			cmd->v6.suspend_time[SCAN_LB_LMAC_IDX] =
				cpu_to_le32(timing->suspend_time);
		} else {
			cmd->v1.scan_priority =
				cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
			cmd->v1.max_out_time =
				cpu_to_le32(timing->max_out_time);
			cmd->v1.suspend_time =
				cpu_to_le32(timing->suspend_time);
		}
	}

	if (iwl_mvm_is_regular_scan(params))
		cmd->ooc_priority = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
	else
		cmd->ooc_priority = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_2);
}