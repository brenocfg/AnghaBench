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
struct TYPE_2__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_1__ fwrt; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTDP_CMD_OPERATION_STOP ; 
 size_t EIO ; 
 size_t EOPNOTSUPP ; 
 scalar_t__ IWL_UCODE_REGULAR ; 
 int iwl_mvm_ctdp_command (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_is_ctdp_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_stop_ctdp_write(struct iwl_mvm *mvm, char *buf,
					 size_t count, loff_t *ppos)
{
	int ret;

	if (!iwl_mvm_is_ctdp_supported(mvm))
		return -EOPNOTSUPP;

	if (!iwl_mvm_firmware_running(mvm) ||
	    mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR)
		return -EIO;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_ctdp_command(mvm, CTDP_CMD_OPERATION_STOP, 0);
	mutex_unlock(&mvm->mutex);

	return ret ?: count;
}