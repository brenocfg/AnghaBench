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
struct drm_connector {scalar_t__ connector_type; struct drm_property* colorspace_property; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ DRM_MODE_CONNECTOR_HDMIA ; 
 scalar_t__ DRM_MODE_CONNECTOR_HDMIB ; 
 int /*<<< orphan*/  DRM_MODE_PROP_ENUM ; 
 int ENOMEM ; 
 struct drm_property* drm_property_create_enum (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_colorspaces ; 

int drm_mode_create_colorspace_property(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct drm_property *prop;

	if (connector->connector_type == DRM_MODE_CONNECTOR_HDMIA ||
	    connector->connector_type == DRM_MODE_CONNECTOR_HDMIB) {
		prop = drm_property_create_enum(dev, DRM_MODE_PROP_ENUM,
						"Colorspace",
						hdmi_colorspaces,
						ARRAY_SIZE(hdmi_colorspaces));
		if (!prop)
			return -ENOMEM;
	} else {
		DRM_DEBUG_KMS("Colorspace property not supported\n");
		return 0;
	}

	connector->colorspace_property = prop;

	return 0;
}