#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int const u32 ;
struct drm_property {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {struct drm_property* scaling_mode_property; int /*<<< orphan*/  base; struct drm_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int const BIT (int) ; 
 int /*<<< orphan*/  DRM_MODE_PROP_ENUM ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,struct drm_property*,int /*<<< orphan*/ ) ; 
 int drm_property_add_enum (struct drm_property*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create (struct drm_device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_property_destroy (struct drm_device*,struct drm_property*) ; 
 TYPE_1__* drm_scaling_mode_enum_list ; 
 int hweight32 (unsigned int const) ; 

int drm_connector_attach_scaling_mode_property(struct drm_connector *connector,
					       u32 scaling_mode_mask)
{
	struct drm_device *dev = connector->dev;
	struct drm_property *scaling_mode_property;
	int i;
	const unsigned valid_scaling_mode_mask =
		(1U << ARRAY_SIZE(drm_scaling_mode_enum_list)) - 1;

	if (WARN_ON(hweight32(scaling_mode_mask) < 2 ||
		    scaling_mode_mask & ~valid_scaling_mode_mask))
		return -EINVAL;

	scaling_mode_property =
		drm_property_create(dev, DRM_MODE_PROP_ENUM, "scaling mode",
				    hweight32(scaling_mode_mask));

	if (!scaling_mode_property)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(drm_scaling_mode_enum_list); i++) {
		int ret;

		if (!(BIT(i) & scaling_mode_mask))
			continue;

		ret = drm_property_add_enum(scaling_mode_property,
					    drm_scaling_mode_enum_list[i].type,
					    drm_scaling_mode_enum_list[i].name);

		if (ret) {
			drm_property_destroy(dev, scaling_mode_property);

			return ret;
		}
	}

	drm_object_attach_property(&connector->base,
				   scaling_mode_property, 0);

	connector->scaling_mode_property = scaling_mode_property;

	return 0;
}