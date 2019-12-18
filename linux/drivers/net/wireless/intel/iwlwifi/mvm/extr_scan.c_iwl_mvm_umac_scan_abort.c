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
struct iwl_umac_scan_abort {int /*<<< orphan*/  uid; } ;
struct iwl_mvm {int* scan_uid_status; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ALWAYS_LONG_GROUP ; 
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_mvm*,char*,int) ; 
 int IWL_MVM_SCAN_STOPPING_SHIFT ; 
 int /*<<< orphan*/  SCAN_ABORT_UMAC ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_scan_uid_by_status (struct iwl_mvm*,int) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_umac_scan_abort*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_umac_scan_abort(struct iwl_mvm *mvm, int type)
{
	struct iwl_umac_scan_abort cmd = {};
	int uid, ret;

	lockdep_assert_held(&mvm->mutex);

	/* We should always get a valid index here, because we already
	 * checked that this type of scan was running in the generic
	 * code.
	 */
	uid = iwl_mvm_scan_uid_by_status(mvm, type);
	if (WARN_ON_ONCE(uid < 0))
		return uid;

	cmd.uid = cpu_to_le32(uid);

	IWL_DEBUG_SCAN(mvm, "Sending scan abort, uid %u\n", uid);

	ret = iwl_mvm_send_cmd_pdu(mvm,
				   iwl_cmd_id(SCAN_ABORT_UMAC,
					      IWL_ALWAYS_LONG_GROUP, 0),
				   0, sizeof(cmd), &cmd);
	if (!ret)
		mvm->scan_uid_status[uid] = type << IWL_MVM_SCAN_STOPPING_SHIFT;

	return ret;
}