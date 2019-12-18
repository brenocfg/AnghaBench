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
struct iwl_fw_runtime {int /*<<< orphan*/  fw; int /*<<< orphan*/  trans; } ;
struct iwl_fw_dbg_trigger_tlv {int dummy; } ;
typedef  enum iwl_fw_dbg_trigger { ____Placeholder_iwl_fw_dbg_trigger } iwl_fw_dbg_trigger ;

/* Variables and functions */
 struct iwl_fw_dbg_trigger_tlv* _iwl_fw_dbg_get_trigger (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_check_stop (struct iwl_fw_runtime*,struct wireless_dev*,struct iwl_fw_dbg_trigger_tlv*) ; 
 int /*<<< orphan*/  iwl_fw_dbg_trigger_enabled (int /*<<< orphan*/ ,int const) ; 
 scalar_t__ iwl_trans_dbg_ini_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct iwl_fw_dbg_trigger_tlv*
_iwl_fw_dbg_trigger_on(struct iwl_fw_runtime *fwrt,
		       struct wireless_dev *wdev,
		       const enum iwl_fw_dbg_trigger id)
{
	struct iwl_fw_dbg_trigger_tlv *trig;

	if (iwl_trans_dbg_ini_valid(fwrt->trans))
		return NULL;

	if (!iwl_fw_dbg_trigger_enabled(fwrt->fw, id))
		return NULL;

	trig = _iwl_fw_dbg_get_trigger(fwrt->fw, id);

	if (!iwl_fw_dbg_trigger_check_stop(fwrt, wdev, trig))
		return NULL;

	return trig;
}