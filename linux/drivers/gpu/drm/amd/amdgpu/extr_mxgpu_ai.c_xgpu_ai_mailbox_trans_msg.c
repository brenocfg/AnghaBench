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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;
typedef  enum idh_request { ____Placeholder_idh_request } idh_request ;

/* Variables and functions */
 int /*<<< orphan*/  BIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW0 ; 
 int /*<<< orphan*/  MSGBUF_DATA ; 
 int /*<<< orphan*/  NBIO ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_NO_KIQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW0 ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW1 ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW2 ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW3 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  xgpu_ai_mailbox_set_valid (struct amdgpu_device*,int) ; 
 scalar_t__ xgpu_ai_peek_ack (struct amdgpu_device*) ; 
 int xgpu_ai_poll_ack (struct amdgpu_device*) ; 

__attribute__((used)) static void xgpu_ai_mailbox_trans_msg (struct amdgpu_device *adev,
	      enum idh_request req, u32 data1, u32 data2, u32 data3) {
	u32 reg;
	int r;
	uint8_t trn;

	/* IMPORTANT:
	 * clear TRN_MSG_VALID valid to clear host's RCV_MSG_ACK
	 * and with host's RCV_MSG_ACK cleared hw automatically clear host's RCV_MSG_ACK
	 * which lead to VF's TRN_MSG_ACK cleared, otherwise below xgpu_ai_poll_ack()
	 * will return immediatly
	 */
	do {
		xgpu_ai_mailbox_set_valid(adev, false);
		trn = xgpu_ai_peek_ack(adev);
		if (trn) {
			pr_err("trn=%x ACK should not assert! wait again !\n", trn);
			msleep(1);
		}
	} while(trn);

	reg = RREG32_NO_KIQ(SOC15_REG_OFFSET(NBIO, 0,
					     mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW0));
	reg = REG_SET_FIELD(reg, BIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW0,
			    MSGBUF_DATA, req);
	WREG32_NO_KIQ(SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW0),
		      reg);
	WREG32_NO_KIQ(SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW1),
				data1);
	WREG32_NO_KIQ(SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW2),
				data2);
	WREG32_NO_KIQ(SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF0_MAILBOX_MSGBUF_TRN_DW3),
				data3);

	xgpu_ai_mailbox_set_valid(adev, true);

	/* start to poll ack */
	r = xgpu_ai_poll_ack(adev);
	if (r)
		pr_err("Doesn't get ack from pf, continue\n");

	xgpu_ai_mailbox_set_valid(adev, false);
}