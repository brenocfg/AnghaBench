#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct amdgpu_encoder {TYPE_1__ base; } ;
struct TYPE_4__ {int firmware_flags; } ;
struct amdgpu_device {TYPE_2__ mode_info; } ;

/* Variables and functions */
 int ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_get_backlight_level_from_reg (struct amdgpu_device*) ; 

u8
amdgpu_atombios_encoder_get_backlight_level(struct amdgpu_encoder *amdgpu_encoder)
{
	struct drm_device *dev = amdgpu_encoder->base.dev;
	struct amdgpu_device *adev = dev->dev_private;

	if (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		return 0;

	return amdgpu_atombios_encoder_get_backlight_level_from_reg(adev);
}