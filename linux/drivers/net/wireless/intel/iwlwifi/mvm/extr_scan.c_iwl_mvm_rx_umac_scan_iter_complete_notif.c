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
struct iwl_umac_scan_iter_complete_notif {int /*<<< orphan*/  scanned_channels; int /*<<< orphan*/  status; int /*<<< orphan*/  start_tsf; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {scalar_t__ sched_scan_pass_all; int /*<<< orphan*/  scan_start; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_mvm*,char*,...) ; 
 scalar_t__ SCHED_SCAN_PASS_ALL_ENABLED ; 
 scalar_t__ SCHED_SCAN_PASS_ALL_FOUND ; 
 int /*<<< orphan*/  ieee80211_sched_scan_results (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_umac_scan_iter_complete_notif(struct iwl_mvm *mvm,
					      struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_umac_scan_iter_complete_notif *notif = (void *)pkt->data;

	mvm->scan_start = le64_to_cpu(notif->start_tsf);

	IWL_DEBUG_SCAN(mvm,
		       "UMAC Scan iteration complete: status=0x%x scanned_channels=%d\n",
		       notif->status, notif->scanned_channels);

	if (mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_FOUND) {
		IWL_DEBUG_SCAN(mvm, "Pass all scheduled scan results found\n");
		ieee80211_sched_scan_results(mvm->hw);
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_ENABLED;
	}

	IWL_DEBUG_SCAN(mvm,
		       "UMAC Scan iteration complete: scan started at %llu (TSF)\n",
		       mvm->scan_start);
}