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
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_ME1_PIPE0_INT_CNTL ; 
 int /*<<< orphan*/  mmCP_ME1_PIPE1_INT_CNTL ; 
 int /*<<< orphan*/  mmCP_ME1_PIPE2_INT_CNTL ; 
 int /*<<< orphan*/  mmCP_ME1_PIPE3_INT_CNTL ; 

__attribute__((used)) static void gfx_v8_0_set_compute_eop_interrupt_state(struct amdgpu_device *adev,
						     int me, int pipe,
						     enum amdgpu_interrupt_state state)
{
	u32 mec_int_cntl, mec_int_cntl_reg;

	/*
	 * amdgpu controls only the first MEC. That's why this function only
	 * handles the setting of interrupts for this specific MEC. All other
	 * pipes' interrupts are set by amdkfd.
	 */

	if (me == 1) {
		switch (pipe) {
		case 0:
			mec_int_cntl_reg = mmCP_ME1_PIPE0_INT_CNTL;
			break;
		case 1:
			mec_int_cntl_reg = mmCP_ME1_PIPE1_INT_CNTL;
			break;
		case 2:
			mec_int_cntl_reg = mmCP_ME1_PIPE2_INT_CNTL;
			break;
		case 3:
			mec_int_cntl_reg = mmCP_ME1_PIPE3_INT_CNTL;
			break;
		default:
			DRM_DEBUG("invalid pipe %d\n", pipe);
			return;
		}
	} else {
		DRM_DEBUG("invalid me %d\n", me);
		return;
	}

	switch (state) {
	case AMDGPU_IRQ_STATE_DISABLE:
		mec_int_cntl = RREG32(mec_int_cntl_reg);
		mec_int_cntl &= ~CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK;
		WREG32(mec_int_cntl_reg, mec_int_cntl);
		break;
	case AMDGPU_IRQ_STATE_ENABLE:
		mec_int_cntl = RREG32(mec_int_cntl_reg);
		mec_int_cntl |= CP_INT_CNTL_RING0__TIME_STAMP_INT_ENABLE_MASK;
		WREG32(mec_int_cntl_reg, mec_int_cntl);
		break;
	default:
		break;
	}
}