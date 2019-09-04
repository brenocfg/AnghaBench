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
struct amdgpu_device {int dummy; } ;
typedef  enum idh_event { ____Placeholder_idh_event } idh_event ;

/* Variables and functions */
 int /*<<< orphan*/  NBIO ; 
 int RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW0 ; 

__attribute__((used)) static enum idh_event xgpu_ai_mailbox_peek_msg(struct amdgpu_device *adev)
{
	return RREG32_NO_KIQ(SOC15_REG_OFFSET(NBIO, 0,
				mmBIF_BX_PF0_MAILBOX_MSGBUF_RCV_DW0));
}