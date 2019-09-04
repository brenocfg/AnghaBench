#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int /*<<< orphan*/  transfer; struct device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct tc_data {int rev; int assr; TYPE_1__ aux; TYPE_3__ bridge; int /*<<< orphan*/  connector; struct device* dev; void* regmap; void* refclk; void* reset_gpio; void* sd_gpio; int /*<<< orphan*/  panel; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  TC_IDREG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tc_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_3__*) ; 
 int drm_dp_aux_register (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_dp_aux_unregister (TYPE_1__*) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (void*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tc_data*) ; 
 int regmap_read (void*,int /*<<< orphan*/ ,int*) ; 
 int tc_aux_link_setup (struct tc_data*) ; 
 int /*<<< orphan*/  tc_aux_transfer ; 
 int /*<<< orphan*/  tc_bridge_funcs ; 
 int /*<<< orphan*/  tc_connector_set_polling (struct tc_data*,int /*<<< orphan*/ *) ; 
 int tc_get_display_props (struct tc_data*) ; 
 int /*<<< orphan*/  tc_regmap_config ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tc_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct tc_data *tc;
	int ret;

	tc = devm_kzalloc(dev, sizeof(*tc), GFP_KERNEL);
	if (!tc)
		return -ENOMEM;

	tc->dev = dev;

	/* port@2 is the output port */
	ret = drm_of_find_panel_or_bridge(dev->of_node, 2, 0, &tc->panel, NULL);
	if (ret && ret != -ENODEV)
		return ret;

	/* Shut down GPIO is optional */
	tc->sd_gpio = devm_gpiod_get_optional(dev, "shutdown", GPIOD_OUT_HIGH);
	if (IS_ERR(tc->sd_gpio))
		return PTR_ERR(tc->sd_gpio);

	if (tc->sd_gpio) {
		gpiod_set_value_cansleep(tc->sd_gpio, 0);
		usleep_range(5000, 10000);
	}

	/* Reset GPIO is optional */
	tc->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(tc->reset_gpio))
		return PTR_ERR(tc->reset_gpio);

	if (tc->reset_gpio) {
		gpiod_set_value_cansleep(tc->reset_gpio, 1);
		usleep_range(5000, 10000);
	}

	tc->refclk = devm_clk_get(dev, "ref");
	if (IS_ERR(tc->refclk)) {
		ret = PTR_ERR(tc->refclk);
		dev_err(dev, "Failed to get refclk: %d\n", ret);
		return ret;
	}

	tc->regmap = devm_regmap_init_i2c(client, &tc_regmap_config);
	if (IS_ERR(tc->regmap)) {
		ret = PTR_ERR(tc->regmap);
		dev_err(dev, "Failed to initialize regmap: %d\n", ret);
		return ret;
	}

	ret = regmap_read(tc->regmap, TC_IDREG, &tc->rev);
	if (ret) {
		dev_err(tc->dev, "can not read device ID: %d\n", ret);
		return ret;
	}

	if ((tc->rev != 0x6601) && (tc->rev != 0x6603)) {
		dev_err(tc->dev, "invalid device ID: 0x%08x\n", tc->rev);
		return -EINVAL;
	}

	tc->assr = (tc->rev == 0x6601); /* Enable ASSR for eDP panels */

	ret = tc_aux_link_setup(tc);
	if (ret)
		return ret;

	/* Register DP AUX channel */
	tc->aux.name = "TC358767 AUX i2c adapter";
	tc->aux.dev = tc->dev;
	tc->aux.transfer = tc_aux_transfer;
	ret = drm_dp_aux_register(&tc->aux);
	if (ret)
		return ret;

	ret = tc_get_display_props(tc);
	if (ret)
		goto err_unregister_aux;

	tc_connector_set_polling(tc, &tc->connector);

	tc->bridge.funcs = &tc_bridge_funcs;
	tc->bridge.of_node = dev->of_node;
	drm_bridge_add(&tc->bridge);

	i2c_set_clientdata(client, tc);

	return 0;
err_unregister_aux:
	drm_dp_aux_unregister(&tc->aux);
	return ret;
}