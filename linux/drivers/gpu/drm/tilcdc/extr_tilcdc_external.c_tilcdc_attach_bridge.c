#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tilcdc_drm_private {int /*<<< orphan*/  external_connector; TYPE_1__* external_encoder; int /*<<< orphan*/  crtc; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tilcdc_drm_private* dev_private; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  possible_crtcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_bridge_attach (TYPE_1__*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panel_info_default ; 
 int /*<<< orphan*/  tilcdc_crtc_set_panel_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tilcdc_encoder_find_connector (struct drm_device*,TYPE_1__*) ; 

__attribute__((used)) static
int tilcdc_attach_bridge(struct drm_device *ddev, struct drm_bridge *bridge)
{
	struct tilcdc_drm_private *priv = ddev->dev_private;
	int ret;

	priv->external_encoder->possible_crtcs = BIT(0);

	ret = drm_bridge_attach(priv->external_encoder, bridge, NULL);
	if (ret) {
		dev_err(ddev->dev, "drm_bridge_attach() failed %d\n", ret);
		return ret;
	}

	tilcdc_crtc_set_panel_info(priv->crtc, &panel_info_default);

	priv->external_connector =
		tilcdc_encoder_find_connector(ddev, priv->external_encoder);
	if (!priv->external_connector)
		return -ENODEV;

	return 0;
}