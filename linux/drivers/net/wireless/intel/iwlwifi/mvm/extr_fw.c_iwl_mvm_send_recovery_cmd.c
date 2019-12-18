#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_mvm {int /*<<< orphan*/ * error_recovery_buf; TYPE_2__* fw; } ;
struct iwl_host_cmd {int* len; TYPE_3__* resp_pkt; int /*<<< orphan*/ * dataflags; int /*<<< orphan*/ ** data; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct iwl_fw_error_recovery_cmd {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_4__ {int error_log_size; } ;
struct TYPE_5__ {TYPE_1__ ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int ERROR_RECOVERY_UPDATE_DB ; 
 int /*<<< orphan*/  FW_ERROR_RECOVERY_CMD ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_HCMD_DFL_NOCOPY ; 
 int /*<<< orphan*/  SYSTEM_GROUP ; 
 int /*<<< orphan*/  WIDE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

void iwl_mvm_send_recovery_cmd(struct iwl_mvm *mvm, u32 flags)
{
	u32 error_log_size = mvm->fw->ucode_capa.error_log_size;
	int ret;
	u32 resp;

	struct iwl_fw_error_recovery_cmd recovery_cmd = {
		.flags = cpu_to_le32(flags),
		.buf_size = 0,
	};
	struct iwl_host_cmd host_cmd = {
		.id = WIDE_ID(SYSTEM_GROUP, FW_ERROR_RECOVERY_CMD),
		.flags = CMD_WANT_SKB,
		.data = {&recovery_cmd, },
		.len = {sizeof(recovery_cmd), },
	};

	/* no error log was defined in TLV */
	if (!error_log_size)
		return;

	if (flags & ERROR_RECOVERY_UPDATE_DB) {
		/* no buf was allocated while HW reset */
		if (!mvm->error_recovery_buf)
			return;

		host_cmd.data[1] = mvm->error_recovery_buf;
		host_cmd.len[1] =  error_log_size;
		host_cmd.dataflags[1] = IWL_HCMD_DFL_NOCOPY;
		recovery_cmd.buf_size = cpu_to_le32(error_log_size);
	}

	ret = iwl_mvm_send_cmd(mvm, &host_cmd);
	kfree(mvm->error_recovery_buf);
	mvm->error_recovery_buf = NULL;

	if (ret) {
		IWL_ERR(mvm, "Failed to send recovery cmd %d\n", ret);
		return;
	}

	/* skb respond is only relevant in ERROR_RECOVERY_UPDATE_DB */
	if (flags & ERROR_RECOVERY_UPDATE_DB) {
		resp = le32_to_cpu(*(__le32 *)host_cmd.resp_pkt->data);
		if (resp)
			IWL_ERR(mvm,
				"Failed to send recovery cmd blob was invalid %d\n",
				resp);
	}
}