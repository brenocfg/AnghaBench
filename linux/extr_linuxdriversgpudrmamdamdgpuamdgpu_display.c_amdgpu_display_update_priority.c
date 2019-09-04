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
struct TYPE_2__ {int disp_priority; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int amdgpu_disp_priority ; 

void amdgpu_display_update_priority(struct amdgpu_device *adev)
{
	/* adjustment options for the display watermarks */
	if ((amdgpu_disp_priority == 0) || (amdgpu_disp_priority > 2))
		adev->mode_info.disp_priority = 0;
	else
		adev->mode_info.disp_priority = amdgpu_disp_priority;

}