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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int num_crtc; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
#define  AMDGPU_IRQ_STATE_DISABLE 129 
#define  AMDGPU_IRQ_STATE_ENABLE 128 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  LB_INTERRUPT_MASK ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  VBLANK_INTERRUPT_MASK ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* crtc_offsets ; 
 scalar_t__ mmLB_INTERRUPT_MASK ; 

__attribute__((used)) static void dce_v10_0_set_crtc_vblank_interrupt_state(struct amdgpu_device *adev,
						     int crtc,
						     enum amdgpu_interrupt_state state)
{
	u32 lb_interrupt_mask;

	if (crtc >= adev->mode_info.num_crtc) {
		DRM_DEBUG("invalid crtc %d\n", crtc);
		return;
	}

	switch (state) {
	case AMDGPU_IRQ_STATE_DISABLE:
		lb_interrupt_mask = RREG32(mmLB_INTERRUPT_MASK + crtc_offsets[crtc]);
		lb_interrupt_mask = REG_SET_FIELD(lb_interrupt_mask, LB_INTERRUPT_MASK,
						  VBLANK_INTERRUPT_MASK, 0);
		WREG32(mmLB_INTERRUPT_MASK + crtc_offsets[crtc], lb_interrupt_mask);
		break;
	case AMDGPU_IRQ_STATE_ENABLE:
		lb_interrupt_mask = RREG32(mmLB_INTERRUPT_MASK + crtc_offsets[crtc]);
		lb_interrupt_mask = REG_SET_FIELD(lb_interrupt_mask, LB_INTERRUPT_MASK,
						  VBLANK_INTERRUPT_MASK, 1);
		WREG32(mmLB_INTERRUPT_MASK + crtc_offsets[crtc], lb_interrupt_mask);
		break;
	default:
		break;
	}
}