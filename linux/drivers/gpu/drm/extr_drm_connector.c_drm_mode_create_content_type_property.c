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
struct TYPE_2__ {int /*<<< orphan*/ * content_type_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  drm_content_type_enum_list ; 
 int /*<<< orphan*/ * drm_property_create_enum (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_mode_create_content_type_property(struct drm_device *dev)
{
	if (dev->mode_config.content_type_property)
		return 0;

	dev->mode_config.content_type_property =
		drm_property_create_enum(dev, 0, "content type",
					 drm_content_type_enum_list,
					 ARRAY_SIZE(drm_content_type_enum_list));

	if (dev->mode_config.content_type_property == NULL)
		return -ENOMEM;

	return 0;
}