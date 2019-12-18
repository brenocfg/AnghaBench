#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  notif_wait; TYPE_1__* fw; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int HZ ; 
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_UMAC_SCAN ; 
#define  SCAN_COMPLETE_UMAC 129 
#define  SCAN_OFFLOAD_COMPLETE 128 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iwl_mvm_lmac_scan_abort (struct iwl_mvm*) ; 
 int iwl_mvm_umac_scan_abort (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_scan_stop_wait(struct iwl_mvm *mvm, int type)
{
	struct iwl_notification_wait wait_scan_done;
	static const u16 scan_done_notif[] = { SCAN_COMPLETE_UMAC,
					      SCAN_OFFLOAD_COMPLETE, };
	int ret;

	lockdep_assert_held(&mvm->mutex);

	iwl_init_notification_wait(&mvm->notif_wait, &wait_scan_done,
				   scan_done_notif,
				   ARRAY_SIZE(scan_done_notif),
				   NULL, NULL);

	IWL_DEBUG_SCAN(mvm, "Preparing to stop scan, type %x\n", type);

	if (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN))
		ret = iwl_mvm_umac_scan_abort(mvm, type);
	else
		ret = iwl_mvm_lmac_scan_abort(mvm);

	if (ret) {
		IWL_DEBUG_SCAN(mvm, "couldn't stop scan type %d\n", type);
		iwl_remove_notification(&mvm->notif_wait, &wait_scan_done);
		return ret;
	}

	return iwl_wait_notification(&mvm->notif_wait, &wait_scan_done,
				     1 * HZ);
}