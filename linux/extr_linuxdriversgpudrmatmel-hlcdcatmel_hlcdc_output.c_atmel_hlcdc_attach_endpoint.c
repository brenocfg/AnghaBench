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
struct drm_panel {int dummy; } ;
struct drm_encoder {int possible_crtcs; } ;
struct drm_device {TYPE_1__* dev; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_Unknown ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_bridge*) ; 
 int PTR_ERR (struct drm_bridge*) ; 
 int /*<<< orphan*/  atmel_hlcdc_panel_encoder_funcs ; 
 struct drm_encoder* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (struct drm_encoder*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct drm_panel**,struct drm_bridge**) ; 
 struct drm_bridge* drm_panel_bridge_add (struct drm_panel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_bridge_remove (struct drm_bridge*) ; 

__attribute__((used)) static int atmel_hlcdc_attach_endpoint(struct drm_device *dev, int endpoint)
{
	struct drm_encoder *encoder;
	struct drm_panel *panel;
	struct drm_bridge *bridge;
	int ret;

	ret = drm_of_find_panel_or_bridge(dev->dev->of_node, 0, endpoint,
					  &panel, &bridge);
	if (ret)
		return ret;

	encoder = devm_kzalloc(dev->dev, sizeof(*encoder), GFP_KERNEL);
	if (!encoder)
		return -EINVAL;

	ret = drm_encoder_init(dev, encoder,
			       &atmel_hlcdc_panel_encoder_funcs,
			       DRM_MODE_ENCODER_NONE, NULL);
	if (ret)
		return ret;

	encoder->possible_crtcs = 0x1;

	if (panel) {
		bridge = drm_panel_bridge_add(panel, DRM_MODE_CONNECTOR_Unknown);
		if (IS_ERR(bridge))
			return PTR_ERR(bridge);
	}

	if (bridge) {
		ret = drm_bridge_attach(encoder, bridge, NULL);
		if (!ret)
			return 0;

		if (panel)
			drm_panel_bridge_remove(bridge);
	}

	drm_encoder_cleanup(encoder);

	return ret;
}