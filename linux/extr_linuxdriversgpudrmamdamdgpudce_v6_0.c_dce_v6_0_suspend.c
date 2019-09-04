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
struct TYPE_2__ {int /*<<< orphan*/  bl_level; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_atombios_encoder_get_backlight_level_from_reg (struct amdgpu_device*) ; 
 int dce_v6_0_hw_fini (void*) ; 

__attribute__((used)) static int dce_v6_0_suspend(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	adev->mode_info.bl_level =
		amdgpu_atombios_encoder_get_backlight_level_from_reg(adev);

	return dce_v6_0_hw_fini(handle);
}