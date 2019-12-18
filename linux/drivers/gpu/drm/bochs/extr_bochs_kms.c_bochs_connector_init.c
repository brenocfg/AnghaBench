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
struct drm_device {struct bochs_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct bochs_device {scalar_t__ edid; struct drm_connector connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  bochs_connector_connector_funcs ; 
 int /*<<< orphan*/  bochs_connector_connector_helper_funcs ; 
 int /*<<< orphan*/  bochs_hw_load_edid (struct bochs_device*) ; 
 int /*<<< orphan*/  drm_connector_attach_edid_property (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,scalar_t__) ; 

__attribute__((used)) static void bochs_connector_init(struct drm_device *dev)
{
	struct bochs_device *bochs = dev->dev_private;
	struct drm_connector *connector = &bochs->connector;

	drm_connector_init(dev, connector, &bochs_connector_connector_funcs,
			   DRM_MODE_CONNECTOR_VIRTUAL);
	drm_connector_helper_add(connector,
				 &bochs_connector_connector_helper_funcs);
	drm_connector_register(connector);

	bochs_hw_load_edid(bochs);
	if (bochs->edid) {
		DRM_INFO("Found EDID data blob.\n");
		drm_connector_attach_edid_property(connector);
		drm_connector_update_edid_property(connector, bochs->edid);
	}
}