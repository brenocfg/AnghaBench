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
struct hwrm_error_recovery_qcfg_output {int reg_array_cnt; int /*<<< orphan*/ * delay_after_reset; int /*<<< orphan*/ * reset_reg_val; int /*<<< orphan*/ * reset_reg; int /*<<< orphan*/  reset_inprogress_reg_mask; int /*<<< orphan*/  reset_inprogress_reg; int /*<<< orphan*/  fw_reset_cnt_reg; int /*<<< orphan*/  fw_heartbeat_reg; int /*<<< orphan*/  fw_health_status_reg; int /*<<< orphan*/  max_bailout_time_after_reset; int /*<<< orphan*/  master_func_wait_period_after_reset; int /*<<< orphan*/  normal_func_wait_period; int /*<<< orphan*/  master_func_wait_period; int /*<<< orphan*/  driver_polling_freq; int /*<<< orphan*/  flags; } ;
struct hwrm_error_recovery_qcfg_input {int /*<<< orphan*/  member_0; } ;
struct bnxt_fw_health {int flags; int fw_reset_seq_cnt; int /*<<< orphan*/ * fw_reset_seq_delay_msec; void** fw_reset_seq_vals; void** fw_reset_seq_regs; void* fw_reset_inprog_reg_mask; void** regs; void* post_reset_max_wait_dsecs; void* post_reset_wait_dsecs; void* normal_func_wait_dsecs; void* master_func_wait_dsecs; void* polling_dsecs; } ;
struct bnxt {int fw_cap; int /*<<< orphan*/  hwrm_cmd_lock; struct bnxt_fw_health* fw_health; struct hwrm_error_recovery_qcfg_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_FW_CAP_ERROR_RECOVERY ; 
 int BNXT_FW_CAP_KONG_MB_CHNL ; 
 size_t BNXT_FW_HEALTH_REG ; 
 size_t BNXT_FW_HEARTBEAT_REG ; 
 size_t BNXT_FW_RESET_CNT_REG ; 
 size_t BNXT_FW_RESET_INPROG_REG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERROR_RECOVERY_QCFG_RESP_FLAGS_CO_CPU ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_ERROR_RECOVERY_QCFG ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_error_recovery_qcfg_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_error_recovery_qcfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int bnxt_map_fw_health_regs (struct bnxt*) ; 
 struct bnxt_fw_health* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_hwrm_error_recovery_qcfg(struct bnxt *bp)
{
	struct hwrm_error_recovery_qcfg_output *resp = bp->hwrm_cmd_resp_addr;
	struct bnxt_fw_health *fw_health = bp->fw_health;
	struct hwrm_error_recovery_qcfg_input req = {0};
	int rc, i;

	if (!(bp->fw_cap & BNXT_FW_CAP_ERROR_RECOVERY))
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_ERROR_RECOVERY_QCFG, -1, -1);
	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		goto err_recovery_out;
	if (!fw_health) {
		fw_health = kzalloc(sizeof(*fw_health), GFP_KERNEL);
		bp->fw_health = fw_health;
		if (!fw_health) {
			rc = -ENOMEM;
			goto err_recovery_out;
		}
	}
	fw_health->flags = le32_to_cpu(resp->flags);
	if ((fw_health->flags & ERROR_RECOVERY_QCFG_RESP_FLAGS_CO_CPU) &&
	    !(bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNL)) {
		rc = -EINVAL;
		goto err_recovery_out;
	}
	fw_health->polling_dsecs = le32_to_cpu(resp->driver_polling_freq);
	fw_health->master_func_wait_dsecs =
		le32_to_cpu(resp->master_func_wait_period);
	fw_health->normal_func_wait_dsecs =
		le32_to_cpu(resp->normal_func_wait_period);
	fw_health->post_reset_wait_dsecs =
		le32_to_cpu(resp->master_func_wait_period_after_reset);
	fw_health->post_reset_max_wait_dsecs =
		le32_to_cpu(resp->max_bailout_time_after_reset);
	fw_health->regs[BNXT_FW_HEALTH_REG] =
		le32_to_cpu(resp->fw_health_status_reg);
	fw_health->regs[BNXT_FW_HEARTBEAT_REG] =
		le32_to_cpu(resp->fw_heartbeat_reg);
	fw_health->regs[BNXT_FW_RESET_CNT_REG] =
		le32_to_cpu(resp->fw_reset_cnt_reg);
	fw_health->regs[BNXT_FW_RESET_INPROG_REG] =
		le32_to_cpu(resp->reset_inprogress_reg);
	fw_health->fw_reset_inprog_reg_mask =
		le32_to_cpu(resp->reset_inprogress_reg_mask);
	fw_health->fw_reset_seq_cnt = resp->reg_array_cnt;
	if (fw_health->fw_reset_seq_cnt >= 16) {
		rc = -EINVAL;
		goto err_recovery_out;
	}
	for (i = 0; i < fw_health->fw_reset_seq_cnt; i++) {
		fw_health->fw_reset_seq_regs[i] =
			le32_to_cpu(resp->reset_reg[i]);
		fw_health->fw_reset_seq_vals[i] =
			le32_to_cpu(resp->reset_reg_val[i]);
		fw_health->fw_reset_seq_delay_msec[i] =
			resp->delay_after_reset[i];
	}
err_recovery_out:
	mutex_unlock(&bp->hwrm_cmd_lock);
	if (!rc)
		rc = bnxt_map_fw_health_regs(bp);
	if (rc)
		bp->fw_cap &= ~BNXT_FW_CAP_ERROR_RECOVERY;
	return rc;
}