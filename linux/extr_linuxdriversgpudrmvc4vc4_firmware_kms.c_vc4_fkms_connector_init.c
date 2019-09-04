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
struct drm_connector {int polled; scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; } ;
struct vc4_fkms_connector {struct drm_encoder* encoder; struct drm_connector base; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int ENOMEM ; 
 struct drm_connector* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vc4_fkms_connector* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc4_fkms_connector_destroy (struct drm_connector*) ; 
 int /*<<< orphan*/  vc4_fkms_connector_funcs ; 
 int /*<<< orphan*/  vc4_fkms_connector_helper_funcs ; 

__attribute__((used)) static struct drm_connector *vc4_fkms_connector_init(struct drm_device *dev,
						     struct drm_encoder *encoder)
{
	struct drm_connector *connector = NULL;
	struct vc4_fkms_connector *fkms_connector;
	int ret = 0;

	fkms_connector = devm_kzalloc(dev->dev, sizeof(*fkms_connector),
				      GFP_KERNEL);
	if (!fkms_connector) {
		ret = -ENOMEM;
		goto fail;
	}
	connector = &fkms_connector->base;

	fkms_connector->encoder = encoder;

	drm_connector_init(dev, connector, &vc4_fkms_connector_funcs,
			   DRM_MODE_CONNECTOR_HDMIA);
	drm_connector_helper_add(connector, &vc4_fkms_connector_helper_funcs);

	connector->polled = (DRM_CONNECTOR_POLL_CONNECT |
			     DRM_CONNECTOR_POLL_DISCONNECT);

	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	drm_connector_attach_encoder(connector, encoder);

	return connector;

 fail:
	if (connector)
		vc4_fkms_connector_destroy(connector);

	return ERR_PTR(ret);
}