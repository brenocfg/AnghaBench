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
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
#define  AMDGPU_IRQ_STATE_DISABLE 129 
#define  AMDGPU_IRQ_STATE_ENABLE 128 
 int /*<<< orphan*/  CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_INT_CNTL_RING0 ; 

__attribute__((used)) static void gfx_v6_0_set_gfx_eop_interrupt_state(struct amdgpu_device *adev,
						 enum amdgpu_interrupt_state state)
{
	u32 cp_int_cntl;

	switch (state) {
	case AMDGPU_IRQ_STATE_DISABLE:
		cp_int_cntl = RREG32(mmCP_INT_CNTL_RING0);
		cp_int_cntl &= ~CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK;
		WREG32(mmCP_INT_CNTL_RING0, cp_int_cntl);
		break;
	case AMDGPU_IRQ_STATE_ENABLE:
		cp_int_cntl = RREG32(mmCP_INT_CNTL_RING0);
		cp_int_cntl |= CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK;
		WREG32(mmCP_INT_CNTL_RING0, cp_int_cntl);
		break;
	default:
		break;
	}
}