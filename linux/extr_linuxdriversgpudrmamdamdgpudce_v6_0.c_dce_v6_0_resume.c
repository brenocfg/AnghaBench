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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ bl_encoder; int /*<<< orphan*/  bl_level; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_atombios_encoder_set_backlight_level_to_reg (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_display_backlight_get_level (struct amdgpu_device*,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_display_backlight_set_level (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int dce_v6_0_hw_init (void*) ; 

__attribute__((used)) static int dce_v6_0_resume(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int ret;

	amdgpu_atombios_encoder_set_backlight_level_to_reg(adev,
							   adev->mode_info.bl_level);

	ret = dce_v6_0_hw_init(handle);

	/* turn on the BL */
	if (adev->mode_info.bl_encoder) {
		u8 bl_level = amdgpu_display_backlight_get_level(adev,
								  adev->mode_info.bl_encoder);
		amdgpu_display_backlight_set_level(adev, adev->mode_info.bl_encoder,
						    bl_level);
	}

	return ret;
}