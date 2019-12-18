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
struct tfp410_module {int dummy; } ;
struct drm_connector {int polled; scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; } ;
struct tfp410_connector {struct drm_connector base; struct tfp410_module* mod; struct drm_encoder* encoder; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DVID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tfp410_connector* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfp410_connector_destroy (struct drm_connector*) ; 
 int /*<<< orphan*/  tfp410_connector_funcs ; 
 int /*<<< orphan*/  tfp410_connector_helper_funcs ; 

__attribute__((used)) static struct drm_connector *tfp410_connector_create(struct drm_device *dev,
		struct tfp410_module *mod, struct drm_encoder *encoder)
{
	struct tfp410_connector *tfp410_connector;
	struct drm_connector *connector;
	int ret;

	tfp410_connector = devm_kzalloc(dev->dev, sizeof(*tfp410_connector),
					GFP_KERNEL);
	if (!tfp410_connector)
		return NULL;

	tfp410_connector->encoder = encoder;
	tfp410_connector->mod = mod;

	connector = &tfp410_connector->base;

	drm_connector_init(dev, connector, &tfp410_connector_funcs,
			DRM_MODE_CONNECTOR_DVID);
	drm_connector_helper_add(connector, &tfp410_connector_helper_funcs);

	connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			DRM_CONNECTOR_POLL_DISCONNECT;

	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	ret = drm_connector_attach_encoder(connector, encoder);
	if (ret)
		goto fail;

	return connector;

fail:
	tfp410_connector_destroy(connector);
	return NULL;
}