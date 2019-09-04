#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int polled; } ;
struct adv7511 {scalar_t__ type; int /*<<< orphan*/  regmap; TYPE_1__* i2c_main; TYPE_2__ connector; } ;
struct TYPE_5__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7511_INT0_HPD ; 
 int /*<<< orphan*/  ADV7511_REG_INT_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ ADV7533 ; 
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 
 int DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int ENODEV ; 
 int /*<<< orphan*/  adv7511_connector_funcs ; 
 int /*<<< orphan*/  adv7511_connector_helper_funcs ; 
 int adv7533_attach_dsi (struct adv7511*) ; 
 struct adv7511* bridge_to_adv7511 (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7511_bridge_attach(struct drm_bridge *bridge)
{
	struct adv7511 *adv = bridge_to_adv7511(bridge);
	int ret;

	if (!bridge->encoder) {
		DRM_ERROR("Parent encoder object not found");
		return -ENODEV;
	}

	if (adv->i2c_main->irq)
		adv->connector.polled = DRM_CONNECTOR_POLL_HPD;
	else
		adv->connector.polled = DRM_CONNECTOR_POLL_CONNECT |
				DRM_CONNECTOR_POLL_DISCONNECT;

	ret = drm_connector_init(bridge->dev, &adv->connector,
				 &adv7511_connector_funcs,
				 DRM_MODE_CONNECTOR_HDMIA);
	if (ret) {
		DRM_ERROR("Failed to initialize connector with drm\n");
		return ret;
	}
	drm_connector_helper_add(&adv->connector,
				 &adv7511_connector_helper_funcs);
	drm_connector_attach_encoder(&adv->connector, bridge->encoder);

	if (adv->type == ADV7533)
		ret = adv7533_attach_dsi(adv);

	if (adv->i2c_main->irq)
		regmap_write(adv->regmap, ADV7511_REG_INT_ENABLE(0),
			     ADV7511_INT0_HPD);

	return ret;
}