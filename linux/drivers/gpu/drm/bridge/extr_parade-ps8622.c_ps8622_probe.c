#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct ps8622_bridge {scalar_t__ max_lane_count; scalar_t__ lane_count; TYPE_2__ bridge; TYPE_3__* bl; TYPE_3__* gpio_rst; TYPE_3__* gpio_slp; TYPE_3__* v12; struct i2c_client* client; int /*<<< orphan*/  panel; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_7__ {void* brightness; void* max_brightness; } ;
struct TYPE_9__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 void* PS8622_MAX_BRIGHTNESS ; 
 int PTR_ERR (TYPE_3__*) ; 
 TYPE_3__* backlight_device_register (char*,struct device*,struct ps8622_bridge*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ps8622_bridge* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_2__*) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ps8622_bridge*) ; 
 int /*<<< orphan*/  of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  ps8622_backlight_ops ; 
 int /*<<< orphan*/  ps8622_bridge_funcs ; 

__attribute__((used)) static int ps8622_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ps8622_bridge *ps8622;
	int ret;

	ps8622 = devm_kzalloc(dev, sizeof(*ps8622), GFP_KERNEL);
	if (!ps8622)
		return -ENOMEM;

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0, &ps8622->panel, NULL);
	if (ret)
		return ret;

	ps8622->client = client;

	ps8622->v12 = devm_regulator_get(dev, "vdd12");
	if (IS_ERR(ps8622->v12)) {
		dev_info(dev, "no 1.2v regulator found for PS8622\n");
		ps8622->v12 = NULL;
	}

	ps8622->gpio_slp = devm_gpiod_get(dev, "sleep", GPIOD_OUT_HIGH);
	if (IS_ERR(ps8622->gpio_slp)) {
		ret = PTR_ERR(ps8622->gpio_slp);
		dev_err(dev, "cannot get gpio_slp %d\n", ret);
		return ret;
	}

	/*
	 * Assert the reset pin high to avoid the bridge being
	 * initialized prematurely
	 */
	ps8622->gpio_rst = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ps8622->gpio_rst)) {
		ret = PTR_ERR(ps8622->gpio_rst);
		dev_err(dev, "cannot get gpio_rst %d\n", ret);
		return ret;
	}

	ps8622->max_lane_count = id->driver_data;

	if (of_property_read_u32(dev->of_node, "lane-count",
						&ps8622->lane_count)) {
		ps8622->lane_count = ps8622->max_lane_count;
	} else if (ps8622->lane_count > ps8622->max_lane_count) {
		dev_info(dev, "lane-count property is too high,"
						"using max_lane_count\n");
		ps8622->lane_count = ps8622->max_lane_count;
	}

	if (!of_find_property(dev->of_node, "use-external-pwm", NULL)) {
		ps8622->bl = backlight_device_register("ps8622-backlight",
				dev, ps8622, &ps8622_backlight_ops,
				NULL);
		if (IS_ERR(ps8622->bl)) {
			DRM_ERROR("failed to register backlight\n");
			ret = PTR_ERR(ps8622->bl);
			ps8622->bl = NULL;
			return ret;
		}
		ps8622->bl->props.max_brightness = PS8622_MAX_BRIGHTNESS;
		ps8622->bl->props.brightness = PS8622_MAX_BRIGHTNESS;
	}

	ps8622->bridge.funcs = &ps8622_bridge_funcs;
	ps8622->bridge.of_node = dev->of_node;
	drm_bridge_add(&ps8622->bridge);

	i2c_set_clientdata(client, ps8622);

	return 0;
}