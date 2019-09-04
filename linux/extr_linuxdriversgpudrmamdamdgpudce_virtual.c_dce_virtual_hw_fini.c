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
struct TYPE_2__ {int num_crtc; scalar_t__* crtcs; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_IRQ_STATE_DISABLE ; 
 int /*<<< orphan*/  dce_virtual_set_crtc_vblank_interrupt_state (struct amdgpu_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dce_virtual_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i = 0;

	for (i = 0; i<adev->mode_info.num_crtc; i++)
		if (adev->mode_info.crtcs[i])
			dce_virtual_set_crtc_vblank_interrupt_state(adev, i, AMDGPU_IRQ_STATE_DISABLE);

	return 0;
}