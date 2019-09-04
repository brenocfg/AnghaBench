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
struct drm_connector {int dummy; } ;
struct panel_bridge {struct drm_connector connector; int /*<<< orphan*/  panel; int /*<<< orphan*/  connector_type; } ;
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENODEV ; 
 struct panel_bridge* drm_bridge_to_panel_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_panel_attach (int /*<<< orphan*/ ,struct drm_connector*) ; 
 int /*<<< orphan*/  panel_bridge_connector_funcs ; 
 int /*<<< orphan*/  panel_bridge_connector_helper_funcs ; 

__attribute__((used)) static int panel_bridge_attach(struct drm_bridge *bridge)
{
	struct panel_bridge *panel_bridge = drm_bridge_to_panel_bridge(bridge);
	struct drm_connector *connector = &panel_bridge->connector;
	int ret;

	if (!bridge->encoder) {
		DRM_ERROR("Missing encoder\n");
		return -ENODEV;
	}

	drm_connector_helper_add(connector,
				 &panel_bridge_connector_helper_funcs);

	ret = drm_connector_init(bridge->dev, connector,
				 &panel_bridge_connector_funcs,
				 panel_bridge->connector_type);
	if (ret) {
		DRM_ERROR("Failed to initialize connector\n");
		return ret;
	}

	drm_connector_attach_encoder(&panel_bridge->connector,
					  bridge->encoder);

	ret = drm_panel_attach(panel_bridge->panel, &panel_bridge->connector);
	if (ret < 0)
		return ret;

	return 0;
}