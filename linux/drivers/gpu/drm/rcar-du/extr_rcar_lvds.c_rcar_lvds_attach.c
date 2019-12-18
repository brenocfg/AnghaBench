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
struct rcar_lvds {int /*<<< orphan*/  panel; scalar_t__ next_bridge; struct drm_connector connector; } ;
struct drm_encoder {int dummy; } ;
struct drm_bridge {int /*<<< orphan*/  dev; struct drm_encoder* encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 struct rcar_lvds* bridge_to_rcar_lvds (struct drm_bridge*) ; 
 int drm_bridge_attach (struct drm_encoder*,scalar_t__,struct drm_bridge*) ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_panel_attach (int /*<<< orphan*/ ,struct drm_connector*) ; 
 int /*<<< orphan*/  rcar_lvds_conn_funcs ; 
 int /*<<< orphan*/  rcar_lvds_conn_helper_funcs ; 

__attribute__((used)) static int rcar_lvds_attach(struct drm_bridge *bridge)
{
	struct rcar_lvds *lvds = bridge_to_rcar_lvds(bridge);
	struct drm_connector *connector = &lvds->connector;
	struct drm_encoder *encoder = bridge->encoder;
	int ret;

	/* If we have a next bridge just attach it. */
	if (lvds->next_bridge)
		return drm_bridge_attach(bridge->encoder, lvds->next_bridge,
					 bridge);

	/* Otherwise if we have a panel, create a connector. */
	if (!lvds->panel)
		return 0;

	ret = drm_connector_init(bridge->dev, connector, &rcar_lvds_conn_funcs,
				 DRM_MODE_CONNECTOR_LVDS);
	if (ret < 0)
		return ret;

	drm_connector_helper_add(connector, &rcar_lvds_conn_helper_funcs);

	ret = drm_connector_attach_encoder(connector, encoder);
	if (ret < 0)
		return ret;

	return drm_panel_attach(lvds->panel, connector);
}