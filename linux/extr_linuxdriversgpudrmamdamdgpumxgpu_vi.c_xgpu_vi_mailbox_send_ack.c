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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAILBOX_CONTROL ; 
 int /*<<< orphan*/  RCV_MSG_ACK ; 
 int /*<<< orphan*/  RCV_MSG_VALID ; 
 int REG_FIELD_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int VI_MAILBOX_TIMEDOUT ; 
 int /*<<< orphan*/  WREG32_NO_KIQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmMAILBOX_CONTROL ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void xgpu_vi_mailbox_send_ack(struct amdgpu_device *adev)
{
	u32 reg;
	int timeout = VI_MAILBOX_TIMEDOUT;
	u32 mask = REG_FIELD_MASK(MAILBOX_CONTROL, RCV_MSG_VALID);

	reg = RREG32_NO_KIQ(mmMAILBOX_CONTROL);
	reg = REG_SET_FIELD(reg, MAILBOX_CONTROL, RCV_MSG_ACK, 1);
	WREG32_NO_KIQ(mmMAILBOX_CONTROL, reg);

	/*Wait for RCV_MSG_VALID to be 0*/
	reg = RREG32_NO_KIQ(mmMAILBOX_CONTROL);
	while (reg & mask) {
		if (timeout <= 0) {
			pr_err("RCV_MSG_VALID is not cleared\n");
			break;
		}
		mdelay(1);
		timeout -=1;

		reg = RREG32_NO_KIQ(mmMAILBOX_CONTROL);
	}
}