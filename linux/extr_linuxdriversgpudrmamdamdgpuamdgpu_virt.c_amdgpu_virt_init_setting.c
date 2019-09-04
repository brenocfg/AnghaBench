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
struct TYPE_2__ {int num_crtc; } ;
struct amdgpu_device {int enable_virtual_display; scalar_t__ pg_flags; scalar_t__ cg_flags; TYPE_1__ mode_info; } ;

/* Variables and functions */

void amdgpu_virt_init_setting(struct amdgpu_device *adev)
{
	/* enable virtual display */
	adev->mode_info.num_crtc = 1;
	adev->enable_virtual_display = true;
	adev->cg_flags = 0;
	adev->pg_flags = 0;
}