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
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  ieee80211_sched_scan_results (int /*<<< orphan*/ ) ; 

void iwl_mvm_rx_scan_match_found(struct iwl_mvm *mvm,
				 struct iwl_rx_cmd_buffer *rxb)
{
	IWL_DEBUG_SCAN(mvm, "Scheduled scan results\n");
	ieee80211_sched_scan_results(mvm->hw);
}