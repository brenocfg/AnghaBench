#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_crtc; } ;
struct amdgpu_device {int enable_virtual_display; scalar_t__ pg_flags; scalar_t__ cg_flags; TYPE_3__* ddev; TYPE_1__ mode_info; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_ATOMIC ; 

void amdgpu_virt_init_setting(struct amdgpu_device *adev)
{
	/* enable virtual display */
	adev->mode_info.num_crtc = 1;
	adev->enable_virtual_display = true;
	adev->ddev->driver->driver_features &= ~DRIVER_ATOMIC;
	adev->cg_flags = 0;
	adev->pg_flags = 0;
}