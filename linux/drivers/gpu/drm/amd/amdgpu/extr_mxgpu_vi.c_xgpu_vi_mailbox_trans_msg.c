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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;
typedef  enum idh_request { ____Placeholder_idh_request } idh_request ;

/* Variables and functions */
 int /*<<< orphan*/  MAILBOX_MSGBUF_TRN_DW0 ; 
 int /*<<< orphan*/  MSGBUF_DATA ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_NO_KIQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMAILBOX_MSGBUF_TRN_DW0 ; 
 int /*<<< orphan*/  xgpu_vi_mailbox_set_valid (struct amdgpu_device*,int) ; 

__attribute__((used)) static void xgpu_vi_mailbox_trans_msg(struct amdgpu_device *adev,
				      enum idh_request req)
{
	u32 reg;

	reg = RREG32_NO_KIQ(mmMAILBOX_MSGBUF_TRN_DW0);
	reg = REG_SET_FIELD(reg, MAILBOX_MSGBUF_TRN_DW0,
			    MSGBUF_DATA, req);
	WREG32_NO_KIQ(mmMAILBOX_MSGBUF_TRN_DW0, reg);

	xgpu_vi_mailbox_set_valid(adev, true);
}