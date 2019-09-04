#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_property {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_property* content_protection_property; int /*<<< orphan*/  base; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_CONTENT_PROTECTION_UNDESIRED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  drm_cp_enum_list ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,struct drm_property*,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create_enum (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_connector_attach_content_protection_property(
		struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct drm_property *prop;

	prop = drm_property_create_enum(dev, 0, "Content Protection",
					drm_cp_enum_list,
					ARRAY_SIZE(drm_cp_enum_list));
	if (!prop)
		return -ENOMEM;

	drm_object_attach_property(&connector->base, prop,
				   DRM_MODE_CONTENT_PROTECTION_UNDESIRED);

	connector->content_protection_property = prop;

	return 0;
}