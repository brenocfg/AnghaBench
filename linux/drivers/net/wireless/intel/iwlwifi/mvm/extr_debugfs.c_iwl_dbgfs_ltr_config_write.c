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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct iwl_ltr_config_cmd {int /*<<< orphan*/ * ltr_cfg_values; int /*<<< orphan*/  static_short; int /*<<< orphan*/  static_long; int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  ltr_config ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  LTR_CONFIG ; 
 int /*<<< orphan*/  iwl_mvm_firmware_running (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_ltr_config_cmd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
iwl_dbgfs_ltr_config_write(struct iwl_mvm *mvm,
			   char *buf, size_t count, loff_t *ppos)
{
	int ret;
	struct iwl_ltr_config_cmd ltr_config = {0};

	if (!iwl_mvm_firmware_running(mvm))
		return -EIO;

	if (sscanf(buf, "%x,%x,%x,%x,%x,%x,%x",
		   &ltr_config.flags,
		   &ltr_config.static_long,
		   &ltr_config.static_short,
		   &ltr_config.ltr_cfg_values[0],
		   &ltr_config.ltr_cfg_values[1],
		   &ltr_config.ltr_cfg_values[2],
		   &ltr_config.ltr_cfg_values[3]) != 7) {
		return -EINVAL;
	}

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_send_cmd_pdu(mvm, LTR_CONFIG, 0, sizeof(ltr_config),
				   &ltr_config);
	mutex_unlock(&mvm->mutex);

	if (ret)
		IWL_ERR(mvm, "failed to send ltr configuration cmd\n");

	return ret ?: count;
}