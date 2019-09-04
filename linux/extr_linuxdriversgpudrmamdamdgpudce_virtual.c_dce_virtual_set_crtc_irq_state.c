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
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum amdgpu_interrupt_state { ____Placeholder_amdgpu_interrupt_state } amdgpu_interrupt_state ;

/* Variables and functions */
 unsigned int AMDGPU_CRTC_IRQ_VBLANK6 ; 
 int EINVAL ; 
 int /*<<< orphan*/  dce_virtual_set_crtc_vblank_interrupt_state (struct amdgpu_device*,unsigned int,int) ; 

__attribute__((used)) static int dce_virtual_set_crtc_irq_state(struct amdgpu_device *adev,
					  struct amdgpu_irq_src *source,
					  unsigned type,
					  enum amdgpu_interrupt_state state)
{
	if (type > AMDGPU_CRTC_IRQ_VBLANK6)
		return -EINVAL;

	dce_virtual_set_crtc_vblank_interrupt_state(adev, type, state);

	return 0;
}