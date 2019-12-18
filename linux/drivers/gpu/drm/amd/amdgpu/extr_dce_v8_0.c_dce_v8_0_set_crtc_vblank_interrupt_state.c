#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int num_crtc; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
#define  AMDGPU_IRQ_STATE_DISABLE 129 
#define  AMDGPU_IRQ_STATE_ENABLE 128 
 scalar_t__ CRTC0_REGISTER_OFFSET ; 
 scalar_t__ CRTC1_REGISTER_OFFSET ; 
 scalar_t__ CRTC2_REGISTER_OFFSET ; 
 scalar_t__ CRTC3_REGISTER_OFFSET ; 
 scalar_t__ CRTC4_REGISTER_OFFSET ; 
 scalar_t__ CRTC5_REGISTER_OFFSET ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 scalar_t__ LB_INTERRUPT_MASK__VBLANK_INTERRUPT_MASK_MASK ; 
 scalar_t__ RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,scalar_t__) ; 
 scalar_t__ mmLB_INTERRUPT_MASK ; 

__attribute__((used)) static void dce_v8_0_set_crtc_vblank_interrupt_state(struct amdgpu_device *adev,
						     int crtc,
						     enum amdgpu_interrupt_state state)
{
	u32 reg_block, lb_interrupt_mask;

	if (crtc >= adev->mode_info.num_crtc) {
		DRM_DEBUG("invalid crtc %d\n", crtc);
		return;
	}

	switch (crtc) {
	case 0:
		reg_block = CRTC0_REGISTER_OFFSET;
		break;
	case 1:
		reg_block = CRTC1_REGISTER_OFFSET;
		break;
	case 2:
		reg_block = CRTC2_REGISTER_OFFSET;
		break;
	case 3:
		reg_block = CRTC3_REGISTER_OFFSET;
		break;
	case 4:
		reg_block = CRTC4_REGISTER_OFFSET;
		break;
	case 5:
		reg_block = CRTC5_REGISTER_OFFSET;
		break;
	default:
		DRM_DEBUG("invalid crtc %d\n", crtc);
		return;
	}

	switch (state) {
	case AMDGPU_IRQ_STATE_DISABLE:
		lb_interrupt_mask = RREG32(mmLB_INTERRUPT_MASK + reg_block);
		lb_interrupt_mask &= ~LB_INTERRUPT_MASK__VBLANK_INTERRUPT_MASK_MASK;
		WREG32(mmLB_INTERRUPT_MASK + reg_block, lb_interrupt_mask);
		break;
	case AMDGPU_IRQ_STATE_ENABLE:
		lb_interrupt_mask = RREG32(mmLB_INTERRUPT_MASK + reg_block);
		lb_interrupt_mask |= LB_INTERRUPT_MASK__VBLANK_INTERRUPT_MASK_MASK;
		WREG32(mmLB_INTERRUPT_MASK + reg_block, lb_interrupt_mask);
		break;
	default:
		break;
	}
}