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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_1__ fwrt; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IWL_UCODE_REGULAR ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_flush_sta_tids (struct iwl_mvm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_flush_tx_path (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 scalar_t__ kstrtou32 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_tx_flush_write(struct iwl_mvm *mvm, char *buf,
					size_t count, loff_t *ppos)
{
	int ret;
	u32 flush_arg;

	if (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR)
		return -EIO;

	if (kstrtou32(buf, 0, &flush_arg))
		return -EINVAL;

	if (iwl_mvm_has_new_tx_api(mvm)) {
		IWL_DEBUG_TX_QUEUES(mvm,
				    "FLUSHING all tids queues on sta_id = %d\n",
				    flush_arg);
		mutex_lock(&mvm->mutex);
		ret = iwl_mvm_flush_sta_tids(mvm, flush_arg, 0xFF, 0) ? : count;
		mutex_unlock(&mvm->mutex);
		return ret;
	}

	IWL_DEBUG_TX_QUEUES(mvm, "FLUSHING queues mask to flush = 0x%x\n",
			    flush_arg);

	mutex_lock(&mvm->mutex);
	ret =  iwl_mvm_flush_tx_path(mvm, flush_arg, 0) ? : count;
	mutex_unlock(&mvm->mutex);

	return ret;
}