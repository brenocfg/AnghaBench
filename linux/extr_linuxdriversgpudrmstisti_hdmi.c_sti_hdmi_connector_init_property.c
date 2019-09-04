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
struct sti_hdmi_connector {struct drm_property* colorspace_property; struct sti_hdmi* hdmi; } ;
struct sti_hdmi {int /*<<< orphan*/  colorspace; } ;
struct drm_property {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_COLORSPACE_MODE ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  colorspace_mode_names ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,struct drm_property*,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create_enum (struct drm_device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sti_hdmi_connector* to_sti_hdmi_connector (struct drm_connector*) ; 

__attribute__((used)) static void sti_hdmi_connector_init_property(struct drm_device *drm_dev,
					     struct drm_connector *connector)
{
	struct sti_hdmi_connector *hdmi_connector
		= to_sti_hdmi_connector(connector);
	struct sti_hdmi *hdmi = hdmi_connector->hdmi;
	struct drm_property *prop;

	/* colorspace property */
	hdmi->colorspace = DEFAULT_COLORSPACE_MODE;
	prop = drm_property_create_enum(drm_dev, 0, "colorspace",
					colorspace_mode_names,
					ARRAY_SIZE(colorspace_mode_names));
	if (!prop) {
		DRM_ERROR("fails to create colorspace property\n");
		return;
	}
	hdmi_connector->colorspace_property = prop;
	drm_object_attach_property(&connector->base, prop, hdmi->colorspace);
}