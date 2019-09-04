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
struct icp_qat_fw_loader_handle {scalar_t__ fw_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCU_CONTROL ; 
 int /*<<< orphan*/  FCU_CTRL_CMD_START ; 
 int /*<<< orphan*/  FCU_STATUS ; 
 unsigned int FCU_STS_DONE_POS ; 
 int /*<<< orphan*/  FW_AUTH_MAX_RETRY ; 
 int /*<<< orphan*/  FW_AUTH_WAIT_PERIOD ; 
 unsigned int GET_CAP_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ) ; 
 unsigned int ICP_QAT_UCLO_AE_ALL_CTX ; 
 int /*<<< orphan*/  SET_CAP_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  qat_hal_enable_ctx (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  qat_hal_put_wakeup_event (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int,int) ; 

void qat_hal_start(struct icp_qat_fw_loader_handle *handle, unsigned char ae,
		   unsigned int ctx_mask)
{
	int retry = 0;
	unsigned int fcu_sts = 0;

	if (handle->fw_auth) {
		SET_CAP_CSR(handle, FCU_CONTROL, FCU_CTRL_CMD_START);
		do {
			msleep(FW_AUTH_WAIT_PERIOD);
			fcu_sts = GET_CAP_CSR(handle, FCU_STATUS);
			if (((fcu_sts >> FCU_STS_DONE_POS) & 0x1))
				return;
		} while (retry++ < FW_AUTH_MAX_RETRY);
		pr_err("QAT: start error (AE 0x%x FCU_STS = 0x%x)\n", ae,
		       fcu_sts);
	} else {
		qat_hal_put_wakeup_event(handle, ae, (~ctx_mask) &
				 ICP_QAT_UCLO_AE_ALL_CTX, 0x10000);
		qat_hal_enable_ctx(handle, ae, ctx_mask);
	}
}