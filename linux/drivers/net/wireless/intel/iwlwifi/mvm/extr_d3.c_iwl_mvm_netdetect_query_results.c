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
struct iwl_scan_offload_profiles_query_v1 {int dummy; } ;
struct iwl_scan_offload_profiles_query {int /*<<< orphan*/  n_scans_done; int /*<<< orphan*/  matches; int /*<<< orphan*/  matched_profiles; } ;
struct iwl_scan_offload_profile_match_v1 {int dummy; } ;
struct iwl_scan_offload_profile_match {int dummy; } ;
struct iwl_mvm_nd_query_results {int /*<<< orphan*/  matches; void* matched_profiles; } ;
struct iwl_mvm {void* last_netdetect_scans; TYPE_1__* fw; } ;
struct iwl_host_cmd {TYPE_2__* resp_pkt; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 int IWL_SCAN_MAX_PROFILES ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_API_SCAN_OFFLOAD_CHANS ; 
 int /*<<< orphan*/  SCAN_OFFLOAD_PROFILES_QUERY_CMD ; 
 scalar_t__ fw_has_api (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 
 int iwl_rx_packet_payload_len (TYPE_2__*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
iwl_mvm_netdetect_query_results(struct iwl_mvm *mvm,
				struct iwl_mvm_nd_query_results *results)
{
	struct iwl_scan_offload_profiles_query *query;
	struct iwl_host_cmd cmd = {
		.id = SCAN_OFFLOAD_PROFILES_QUERY_CMD,
		.flags = CMD_WANT_SKB,
	};
	int ret, len;
	size_t query_len, matches_len;

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	if (ret) {
		IWL_ERR(mvm, "failed to query matched profiles (%d)\n", ret);
		return ret;
	}

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_SCAN_OFFLOAD_CHANS)) {
		query_len = sizeof(struct iwl_scan_offload_profiles_query);
		matches_len = sizeof(struct iwl_scan_offload_profile_match) *
			IWL_SCAN_MAX_PROFILES;
	} else {
		query_len = sizeof(struct iwl_scan_offload_profiles_query_v1);
		matches_len = sizeof(struct iwl_scan_offload_profile_match_v1) *
			IWL_SCAN_MAX_PROFILES;
	}

	len = iwl_rx_packet_payload_len(cmd.resp_pkt);
	if (len < query_len) {
		IWL_ERR(mvm, "Invalid scan offload profiles query response!\n");
		ret = -EIO;
		goto out_free_resp;
	}

	query = (void *)cmd.resp_pkt->data;

	results->matched_profiles = le32_to_cpu(query->matched_profiles);
	memcpy(results->matches, query->matches, matches_len);

#ifdef CONFIG_IWLWIFI_DEBUGFS
	mvm->last_netdetect_scans = le32_to_cpu(query->n_scans_done);
#endif

out_free_resp:
	iwl_free_resp(&cmd);
	return ret;
}