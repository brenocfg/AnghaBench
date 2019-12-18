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
struct TYPE_2__ {int preferred_depth; int /*<<< orphan*/ * helper_private; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; int /*<<< orphan*/ * funcs; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct vkms_device {struct drm_device drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  XRES_MAX ; 
 int /*<<< orphan*/  XRES_MIN ; 
 int /*<<< orphan*/  YRES_MAX ; 
 int /*<<< orphan*/  YRES_MIN ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  vkms_mode_config_helpers ; 
 int /*<<< orphan*/  vkms_mode_funcs ; 
 int vkms_output_init (struct vkms_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vkms_modeset_init(struct vkms_device *vkmsdev)
{
	struct drm_device *dev = &vkmsdev->drm;

	drm_mode_config_init(dev);
	dev->mode_config.funcs = &vkms_mode_funcs;
	dev->mode_config.min_width = XRES_MIN;
	dev->mode_config.min_height = YRES_MIN;
	dev->mode_config.max_width = XRES_MAX;
	dev->mode_config.max_height = YRES_MAX;
	dev->mode_config.preferred_depth = 24;
	dev->mode_config.helper_private = &vkms_mode_config_helpers;

	return vkms_output_init(vkmsdev, 0);
}