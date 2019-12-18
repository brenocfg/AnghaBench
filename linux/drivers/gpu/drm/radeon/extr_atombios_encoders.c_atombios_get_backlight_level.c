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
struct TYPE_3__ {struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; } ;
struct TYPE_4__ {int firmware_flags; } ;
struct radeon_device {TYPE_2__ mode_info; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU ; 
 int /*<<< orphan*/  radeon_atom_get_backlight_level_from_reg (struct radeon_device*) ; 

u8
atombios_get_backlight_level(struct radeon_encoder *radeon_encoder)
{
	struct drm_device *dev = radeon_encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;

	if (!(rdev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		return 0;

	return radeon_atom_get_backlight_level_from_reg(rdev);
}