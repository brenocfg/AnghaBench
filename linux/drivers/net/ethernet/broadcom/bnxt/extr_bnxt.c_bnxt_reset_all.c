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
struct hwrm_fw_reset_input {int /*<<< orphan*/  flags; int /*<<< orphan*/  selfrst_status; int /*<<< orphan*/  embedded_proc_type; int /*<<< orphan*/  resp_addr; int /*<<< orphan*/  member_0; } ;
struct bnxt_fw_health {int flags; int fw_reset_seq_cnt; } ;
struct bnxt {int /*<<< orphan*/  fw_reset_timestamp; int /*<<< orphan*/  dev; int /*<<< orphan*/  hwrm_cmd_kong_resp_dma_addr; struct bnxt_fw_health* fw_health; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int ERROR_RECOVERY_QCFG_RESP_FLAGS_CO_CPU ; 
 int ERROR_RECOVERY_QCFG_RESP_FLAGS_HOST ; 
 int /*<<< orphan*/  FW_RESET_REQ_EMBEDDED_PROC_TYPE_CHIP ; 
 int /*<<< orphan*/  FW_RESET_REQ_FLAGS_RESET_GRACEFUL ; 
 int /*<<< orphan*/  FW_RESET_REQ_SELFRST_STATUS_SELFRSTASAP ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FW_RESET ; 
 int /*<<< orphan*/  bnxt_fw_reset_writel (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_fw_reset_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_fw_reset_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void bnxt_reset_all(struct bnxt *bp)
{
	struct bnxt_fw_health *fw_health = bp->fw_health;
	int i;

	if (fw_health->flags & ERROR_RECOVERY_QCFG_RESP_FLAGS_HOST) {
		for (i = 0; i < fw_health->fw_reset_seq_cnt; i++)
			bnxt_fw_reset_writel(bp, i);
	} else if (fw_health->flags & ERROR_RECOVERY_QCFG_RESP_FLAGS_CO_CPU) {
		struct hwrm_fw_reset_input req = {0};
		int rc;

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FW_RESET, -1, -1);
		req.resp_addr = cpu_to_le64(bp->hwrm_cmd_kong_resp_dma_addr);
		req.embedded_proc_type = FW_RESET_REQ_EMBEDDED_PROC_TYPE_CHIP;
		req.selfrst_status = FW_RESET_REQ_SELFRST_STATUS_SELFRSTASAP;
		req.flags = FW_RESET_REQ_FLAGS_RESET_GRACEFUL;
		rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
		if (rc)
			netdev_warn(bp->dev, "Unable to reset FW rc=%d\n", rc);
	}
	bp->fw_reset_timestamp = jiffies;
}