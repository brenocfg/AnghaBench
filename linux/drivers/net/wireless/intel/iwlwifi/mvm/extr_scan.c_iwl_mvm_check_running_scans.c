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
struct iwl_mvm {int scan_status; scalar_t__ max_scans; TYPE_1__* fw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
#define  IWL_MVM_SCAN_NETDETECT 130 
#define  IWL_MVM_SCAN_REGULAR 129 
 int IWL_MVM_SCAN_REGULAR_MASK ; 
#define  IWL_MVM_SCAN_SCHED 128 
 int IWL_MVM_SCAN_SCHED_MASK ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_num_scans (struct iwl_mvm*) ; 
 int iwl_mvm_scan_stop (struct iwl_mvm*,int const,int) ; 

__attribute__((used)) static int iwl_mvm_check_running_scans(struct iwl_mvm *mvm, int type)
{
	bool unified_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);

	/* This looks a bit arbitrary, but the idea is that if we run
	 * out of possible simultaneous scans and the userspace is
	 * trying to run a scan type that is already running, we
	 * return -EBUSY.  But if the userspace wants to start a
	 * different type of scan, we stop the opposite type to make
	 * space for the new request.  The reason is backwards
	 * compatibility with old wpa_supplicant that wouldn't stop a
	 * scheduled scan before starting a normal scan.
	 */

	/* FW supports only a single periodic scan */
	if ((type == IWL_MVM_SCAN_SCHED || type == IWL_MVM_SCAN_NETDETECT) &&
	    mvm->scan_status & (IWL_MVM_SCAN_SCHED | IWL_MVM_SCAN_NETDETECT))
		return -EBUSY;

	if (iwl_mvm_num_scans(mvm) < mvm->max_scans)
		return 0;

	/* Use a switch, even though this is a bitmask, so that more
	 * than one bits set will fall in default and we will warn.
	 */
	switch (type) {
	case IWL_MVM_SCAN_REGULAR:
		if (mvm->scan_status & IWL_MVM_SCAN_REGULAR_MASK)
			return -EBUSY;
		return iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_SCHED, true);
	case IWL_MVM_SCAN_SCHED:
		if (mvm->scan_status & IWL_MVM_SCAN_SCHED_MASK)
			return -EBUSY;
		return iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_REGULAR, true);
	case IWL_MVM_SCAN_NETDETECT:
		/* For non-unified images, there's no need to stop
		 * anything for net-detect since the firmware is
		 * restarted anyway.  This way, any sched scans that
		 * were running will be restarted when we resume.
		 */
		if (!unified_image)
			return 0;

		/* If this is a unified image and we ran out of scans,
		 * we need to stop something.  Prefer stopping regular
		 * scans, because the results are useless at this
		 * point, and we should be able to keep running
		 * another scheduled scan while suspended.
		 */
		if (mvm->scan_status & IWL_MVM_SCAN_REGULAR_MASK)
			return iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_REGULAR,
						 true);
		if (mvm->scan_status & IWL_MVM_SCAN_SCHED_MASK)
			return iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_SCHED,
						 true);
		/* Something is wrong if no scan was running but we
		 * ran out of scans.
		 */
		/* fall through */
	default:
		WARN_ON(1);
		break;
	}

	return -EIO;
}