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
typedef  enum idh_event { ____Placeholder_idh_event } idh_event ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NBIO ; 
 int RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW0 ; 
 int /*<<< orphan*/  xgpu_ai_mailbox_send_ack (struct amdgpu_device*) ; 

__attribute__((used)) static int xgpu_ai_mailbox_rcv_msg(struct amdgpu_device *adev,
				   enum idh_event event)
{
	u32 reg;

	reg = RREG32_NO_KIQ(SOC15_REG_OFFSET(NBIO, 0,
					     mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW0));
	if (reg != event)
		return -ENOENT;

	xgpu_ai_mailbox_send_ack(adev);

	return 0;
}