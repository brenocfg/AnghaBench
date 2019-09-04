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
struct drm_psb_private {struct drm_property* broadcast_rgb_property; } ;
struct drm_property {int dummy; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;
struct drm_connector {int /*<<< orphan*/  base; struct drm_device* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_MODE_PROP_ENUM ; 
 int /*<<< orphan*/ * broadcast_rgb_names ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,struct drm_property*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_add_enum (struct drm_property*,int,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create (struct drm_device*,int /*<<< orphan*/ ,char*,int) ; 

void cdv_intel_attach_broadcast_rgb_property(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct drm_property *prop;
	int i;

	prop = dev_priv->broadcast_rgb_property;
	if (prop == NULL) {
		prop = drm_property_create(dev, DRM_MODE_PROP_ENUM,
					   "Broadcast RGB",
					   ARRAY_SIZE(broadcast_rgb_names));
		if (prop == NULL)
			return;

		for (i = 0; i < ARRAY_SIZE(broadcast_rgb_names); i++)
			drm_property_add_enum(prop, i, broadcast_rgb_names[i]);

		dev_priv->broadcast_rgb_property = prop;
	}

	drm_object_attach_property(&connector->base, prop, 0);
}