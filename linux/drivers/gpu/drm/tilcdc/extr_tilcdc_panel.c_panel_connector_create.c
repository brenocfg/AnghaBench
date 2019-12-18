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
struct panel_module {int dummy; } ;
struct drm_connector {scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; } ;
struct panel_connector {struct drm_connector base; struct panel_module* mod; struct drm_encoder* encoder; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct panel_connector* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panel_connector_destroy (struct drm_connector*) ; 
 int /*<<< orphan*/  panel_connector_funcs ; 
 int /*<<< orphan*/  panel_connector_helper_funcs ; 

__attribute__((used)) static struct drm_connector *panel_connector_create(struct drm_device *dev,
		struct panel_module *mod, struct drm_encoder *encoder)
{
	struct panel_connector *panel_connector;
	struct drm_connector *connector;
	int ret;

	panel_connector = devm_kzalloc(dev->dev, sizeof(*panel_connector),
				       GFP_KERNEL);
	if (!panel_connector)
		return NULL;

	panel_connector->encoder = encoder;
	panel_connector->mod = mod;

	connector = &panel_connector->base;

	drm_connector_init(dev, connector, &panel_connector_funcs,
			DRM_MODE_CONNECTOR_LVDS);
	drm_connector_helper_add(connector, &panel_connector_helper_funcs);

	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	ret = drm_connector_attach_encoder(connector, encoder);
	if (ret)
		goto fail;

	return connector;

fail:
	panel_connector_destroy(connector);
	return NULL;
}