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
struct TYPE_4__ {struct drm_device* dev; } ;
struct radeon_encoder {int devices; TYPE_2__ base; } ;
struct radeon_device {scalar_t__ family; scalar_t__ is_atom_bios; TYPE_1__* pdev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct TYPE_3__ {int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 int ATOM_DEVICE_LCD_SUPPORT ; 
 scalar_t__ CHIP_R600 ; 
 int /*<<< orphan*/  radeon_atom_backlight_init (struct radeon_encoder*,struct drm_connector*) ; 
 int radeon_backlight ; 
 int /*<<< orphan*/  radeon_legacy_backlight_init (struct radeon_encoder*,struct drm_connector*) ; 

__attribute__((used)) static void radeon_encoder_add_backlight(struct radeon_encoder *radeon_encoder,
					 struct drm_connector *connector)
{
	struct drm_device *dev = radeon_encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	bool use_bl = false;

	if (!(radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)))
		return;

	if (radeon_backlight == 0) {
		return;
	} else if (radeon_backlight == 1) {
		use_bl = true;
	} else if (radeon_backlight == -1) {
		/* Quirks */
		/* Amilo Xi 2550 only works with acpi bl */
		if ((rdev->pdev->device == 0x9583) &&
		    (rdev->pdev->subsystem_vendor == 0x1734) &&
		    (rdev->pdev->subsystem_device == 0x1107))
			use_bl = false;
/* Older PPC macs use on-GPU backlight controller */
#ifndef CONFIG_PPC_PMAC
		/* disable native backlight control on older asics */
		else if (rdev->family < CHIP_R600)
			use_bl = false;
#endif
		else
			use_bl = true;
	}

	if (use_bl) {
		if (rdev->is_atom_bios)
			radeon_atom_backlight_init(radeon_encoder, connector);
		else
			radeon_legacy_backlight_init(radeon_encoder, connector);
	}
}