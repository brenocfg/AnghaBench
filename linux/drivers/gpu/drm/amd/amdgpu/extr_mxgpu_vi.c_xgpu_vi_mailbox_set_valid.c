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

/* Variables and functions */
 int /*<<< orphan*/  MAILBOX_CONTROL ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_NO_KIQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRN_MSG_VALID ; 
 int /*<<< orphan*/  WREG32_NO_KIQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMAILBOX_CONTROL ; 

__attribute__((used)) static void xgpu_vi_mailbox_set_valid(struct amdgpu_device *adev, bool val)
{
	u32 reg;

	reg = RREG32_NO_KIQ(mmMAILBOX_CONTROL);
	reg = REG_SET_FIELD(reg, MAILBOX_CONTROL,
			    TRN_MSG_VALID, val ? 1 : 0);
	WREG32_NO_KIQ(mmMAILBOX_CONTROL, reg);
}