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
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int SCAN_OFFLOAD_PROBE_REQ_SIZE ; 
 scalar_t__ iwl_mvm_rrm_scan_needed (struct iwl_mvm*) ; 

__attribute__((used)) static int iwl_mvm_max_scan_ie_fw_cmd_room(struct iwl_mvm *mvm)
{
	int max_probe_len;

	max_probe_len = SCAN_OFFLOAD_PROBE_REQ_SIZE;

	/* we create the 802.11 header and SSID element */
	max_probe_len -= 24 + 2;

	/* DS parameter set element is added on 2.4GHZ band if required */
	if (iwl_mvm_rrm_scan_needed(mvm))
		max_probe_len -= 3;

	return max_probe_len;
}