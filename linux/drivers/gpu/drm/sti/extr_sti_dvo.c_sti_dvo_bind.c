#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sti_dvo_connector {struct drm_encoder* encoder; struct sti_dvo* dvo; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct sti_dvo {struct drm_encoder* encoder; struct drm_bridge* bridge; TYPE_1__ dev; struct drm_device* drm_dev; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  polled; } ;
struct drm_bridge {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; struct sti_dvo* driver_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sti_dvo* dev_get_drvdata (struct device*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_add (struct drm_bridge*) ; 
 int drm_bridge_attach (struct drm_encoder*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_bridge_remove (struct drm_bridge*) ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_dvo_bridge_funcs ; 
 int /*<<< orphan*/  sti_dvo_connector_funcs ; 
 int /*<<< orphan*/  sti_dvo_connector_helper_funcs ; 
 struct drm_encoder* sti_dvo_find_encoder (struct drm_device*) ; 

__attribute__((used)) static int sti_dvo_bind(struct device *dev, struct device *master, void *data)
{
	struct sti_dvo *dvo = dev_get_drvdata(dev);
	struct drm_device *drm_dev = data;
	struct drm_encoder *encoder;
	struct sti_dvo_connector *connector;
	struct drm_connector *drm_connector;
	struct drm_bridge *bridge;
	int err;

	/* Set the drm device handle */
	dvo->drm_dev = drm_dev;

	encoder = sti_dvo_find_encoder(drm_dev);
	if (!encoder)
		return -ENOMEM;

	connector = devm_kzalloc(dev, sizeof(*connector), GFP_KERNEL);
	if (!connector)
		return -ENOMEM;

	connector->dvo = dvo;

	bridge = devm_kzalloc(dev, sizeof(*bridge), GFP_KERNEL);
	if (!bridge)
		return -ENOMEM;

	bridge->driver_private = dvo;
	bridge->funcs = &sti_dvo_bridge_funcs;
	bridge->of_node = dvo->dev.of_node;
	drm_bridge_add(bridge);

	err = drm_bridge_attach(encoder, bridge, NULL);
	if (err) {
		DRM_ERROR("Failed to attach bridge\n");
		return err;
	}

	dvo->bridge = bridge;
	connector->encoder = encoder;
	dvo->encoder = encoder;

	drm_connector = (struct drm_connector *)connector;

	drm_connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_init(drm_dev, drm_connector,
			   &sti_dvo_connector_funcs, DRM_MODE_CONNECTOR_LVDS);
	drm_connector_helper_add(drm_connector,
				 &sti_dvo_connector_helper_funcs);

	err = drm_connector_attach_encoder(drm_connector, encoder);
	if (err) {
		DRM_ERROR("Failed to attach a connector to a encoder\n");
		goto err_sysfs;
	}

	return 0;

err_sysfs:
	drm_bridge_remove(bridge);
	return -EINVAL;
}