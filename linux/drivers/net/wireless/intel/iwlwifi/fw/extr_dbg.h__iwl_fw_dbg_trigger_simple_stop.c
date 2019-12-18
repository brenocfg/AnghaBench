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
struct wireless_dev {int dummy; } ;
struct iwl_fw_runtime {int dummy; } ;
struct iwl_fw_dbg_trigger_tlv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (struct iwl_fw_runtime*,struct iwl_fw_dbg_trigger_tlv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_check_stop (struct iwl_fw_runtime*,struct wireless_dev*,struct iwl_fw_dbg_trigger_tlv*) ; 

__attribute__((used)) static inline void
_iwl_fw_dbg_trigger_simple_stop(struct iwl_fw_runtime *fwrt,
				struct wireless_dev *wdev,
				struct iwl_fw_dbg_trigger_tlv *trigger)
{
	if (!trigger)
		return;

	if (!iwl_fw_dbg_trigger_check_stop(fwrt, wdev, trigger))
		return;

	iwl_fw_dbg_collect_trig(fwrt, trigger, NULL);
}