#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_panel {int dummy; } ;
struct drm_device {TYPE_4__* dev; } ;
struct drm_bridge {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int possible_crtcs; } ;
struct atmel_hlcdc_rgb_output {scalar_t__ bus_fmt; TYPE_1__ encoder; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_Unknown ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_NONE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_bridge*) ; 
 int PTR_ERR (struct drm_bridge*) ; 
 scalar_t__ atmel_hlcdc_of_bus_fmt (struct device_node*) ; 
 int /*<<< orphan*/  atmel_hlcdc_panel_encoder_funcs ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 struct atmel_hlcdc_rgb_output* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (TYPE_1__*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (TYPE_1__*) ; 
 int drm_encoder_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct drm_panel**,struct drm_bridge**) ; 
 struct drm_bridge* drm_panel_bridge_add (struct drm_panel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_bridge_remove (struct drm_bridge*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int atmel_hlcdc_attach_endpoint(struct drm_device *dev, int endpoint)
{
	struct atmel_hlcdc_rgb_output *output;
	struct device_node *ep;
	struct drm_panel *panel;
	struct drm_bridge *bridge;
	int ret;

	ep = of_graph_get_endpoint_by_regs(dev->dev->of_node, 0, endpoint);
	if (!ep)
		return -ENODEV;

	ret = drm_of_find_panel_or_bridge(dev->dev->of_node, 0, endpoint,
					  &panel, &bridge);
	if (ret) {
		of_node_put(ep);
		return ret;
	}

	output = devm_kzalloc(dev->dev, sizeof(*output), GFP_KERNEL);
	if (!output) {
		of_node_put(ep);
		return -ENOMEM;
	}

	output->bus_fmt = atmel_hlcdc_of_bus_fmt(ep);
	of_node_put(ep);
	if (output->bus_fmt < 0) {
		dev_err(dev->dev, "endpoint %d: invalid bus width\n", endpoint);
		return -EINVAL;
	}

	ret = drm_encoder_init(dev, &output->encoder,
			       &atmel_hlcdc_panel_encoder_funcs,
			       DRM_MODE_ENCODER_NONE, NULL);
	if (ret)
		return ret;

	output->encoder.possible_crtcs = 0x1;

	if (panel) {
		bridge = drm_panel_bridge_add(panel, DRM_MODE_CONNECTOR_Unknown);
		if (IS_ERR(bridge))
			return PTR_ERR(bridge);
	}

	if (bridge) {
		ret = drm_bridge_attach(&output->encoder, bridge, NULL);
		if (!ret)
			return 0;

		if (panel)
			drm_panel_bridge_remove(bridge);
	}

	drm_encoder_cleanup(&output->encoder);

	return ret;
}