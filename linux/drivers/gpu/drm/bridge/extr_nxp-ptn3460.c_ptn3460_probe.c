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
struct TYPE_2__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct ptn3460_bridge {TYPE_1__ bridge; int /*<<< orphan*/  edid_emulation; void* gpio_rst_n; void* gpio_pd_n; struct i2c_client* client; int /*<<< orphan*/  panel; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ptn3460_bridge* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_1__*) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ptn3460_bridge*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptn3460_bridge_funcs ; 

__attribute__((used)) static int ptn3460_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ptn3460_bridge *ptn_bridge;
	int ret;

	ptn_bridge = devm_kzalloc(dev, sizeof(*ptn_bridge), GFP_KERNEL);
	if (!ptn_bridge) {
		return -ENOMEM;
	}

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0, &ptn_bridge->panel, NULL);
	if (ret)
		return ret;

	ptn_bridge->client = client;

	ptn_bridge->gpio_pd_n = devm_gpiod_get(&client->dev, "powerdown",
					       GPIOD_OUT_HIGH);
	if (IS_ERR(ptn_bridge->gpio_pd_n)) {
		ret = PTR_ERR(ptn_bridge->gpio_pd_n);
		dev_err(dev, "cannot get gpio_pd_n %d\n", ret);
		return ret;
	}

	/*
	 * Request the reset pin low to avoid the bridge being
	 * initialized prematurely
	 */
	ptn_bridge->gpio_rst_n = devm_gpiod_get(&client->dev, "reset",
						GPIOD_OUT_LOW);
	if (IS_ERR(ptn_bridge->gpio_rst_n)) {
		ret = PTR_ERR(ptn_bridge->gpio_rst_n);
		DRM_ERROR("cannot get gpio_rst_n %d\n", ret);
		return ret;
	}

	ret = of_property_read_u32(dev->of_node, "edid-emulation",
			&ptn_bridge->edid_emulation);
	if (ret) {
		dev_err(dev, "Can't read EDID emulation value\n");
		return ret;
	}

	ptn_bridge->bridge.funcs = &ptn3460_bridge_funcs;
	ptn_bridge->bridge.of_node = dev->of_node;
	drm_bridge_add(&ptn_bridge->bridge);

	i2c_set_clientdata(client, ptn_bridge);

	return 0;
}