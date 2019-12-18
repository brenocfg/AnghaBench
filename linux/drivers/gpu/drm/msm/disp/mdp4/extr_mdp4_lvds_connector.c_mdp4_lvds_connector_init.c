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
struct drm_connector {scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; scalar_t__ polled; } ;
struct mdp4_lvds_connector {struct drm_connector base; struct device_node* panel_node; struct drm_encoder* encoder; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_connector* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mdp4_lvds_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp4_lvds_connector_funcs ; 
 int /*<<< orphan*/  mdp4_lvds_connector_helper_funcs ; 

struct drm_connector *mdp4_lvds_connector_init(struct drm_device *dev,
		struct device_node *panel_node, struct drm_encoder *encoder)
{
	struct drm_connector *connector = NULL;
	struct mdp4_lvds_connector *mdp4_lvds_connector;

	mdp4_lvds_connector = kzalloc(sizeof(*mdp4_lvds_connector), GFP_KERNEL);
	if (!mdp4_lvds_connector)
		return ERR_PTR(-ENOMEM);

	mdp4_lvds_connector->encoder = encoder;
	mdp4_lvds_connector->panel_node = panel_node;

	connector = &mdp4_lvds_connector->base;

	drm_connector_init(dev, connector, &mdp4_lvds_connector_funcs,
			DRM_MODE_CONNECTOR_LVDS);
	drm_connector_helper_add(connector, &mdp4_lvds_connector_helper_funcs);

	connector->polled = 0;

	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	drm_connector_attach_encoder(connector, encoder);

	return connector;
}