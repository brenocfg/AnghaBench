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
struct TYPE_2__ {void* tv_bottom_margin_property; void* tv_top_margin_property; void* tv_right_margin_property; void* tv_left_margin_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* drm_property_create_range (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int drm_mode_create_tv_margin_properties(struct drm_device *dev)
{
	if (dev->mode_config.tv_left_margin_property)
		return 0;

	dev->mode_config.tv_left_margin_property =
		drm_property_create_range(dev, 0, "left margin", 0, 100);
	if (!dev->mode_config.tv_left_margin_property)
		return -ENOMEM;

	dev->mode_config.tv_right_margin_property =
		drm_property_create_range(dev, 0, "right margin", 0, 100);
	if (!dev->mode_config.tv_right_margin_property)
		return -ENOMEM;

	dev->mode_config.tv_top_margin_property =
		drm_property_create_range(dev, 0, "top margin", 0, 100);
	if (!dev->mode_config.tv_top_margin_property)
		return -ENOMEM;

	dev->mode_config.tv_bottom_margin_property =
		drm_property_create_range(dev, 0, "bottom margin", 0, 100);
	if (!dev->mode_config.tv_bottom_margin_property)
		return -ENOMEM;

	return 0;
}