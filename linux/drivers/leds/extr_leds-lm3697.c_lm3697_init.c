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
struct lm3697_led {int /*<<< orphan*/  lmu_data; } ;
struct lm3697 {int bank_cfg; TYPE_1__* client; struct lm3697_led* leds; int /*<<< orphan*/  regmap; scalar_t__ enable_gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM3697_CTRL_ENABLE ; 
 int LM3697_MAX_CONTROL_BANKS ; 
 int /*<<< orphan*/  LM3697_OUTPUT_CONFIG ; 
 int /*<<< orphan*/  LM3697_RESET ; 
 int LM3697_SW_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gpiod_direction_output (scalar_t__,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ti_lmu_common_set_ramp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3697_init(struct lm3697 *priv)
{
	struct lm3697_led *led;
	int i, ret;

	if (priv->enable_gpio) {
		gpiod_direction_output(priv->enable_gpio, 1);
	} else {
		ret = regmap_write(priv->regmap, LM3697_RESET, LM3697_SW_RESET);
		if (ret) {
			dev_err(&priv->client->dev, "Cannot reset the device\n");
			goto out;
		}
	}

	ret = regmap_write(priv->regmap, LM3697_CTRL_ENABLE, 0x0);
	if (ret) {
		dev_err(&priv->client->dev, "Cannot write ctrl enable\n");
		goto out;
	}

	ret = regmap_write(priv->regmap, LM3697_OUTPUT_CONFIG, priv->bank_cfg);
	if (ret)
		dev_err(&priv->client->dev, "Cannot write OUTPUT config\n");

	for (i = 0; i < LM3697_MAX_CONTROL_BANKS; i++) {
		led = &priv->leds[i];
		ret = ti_lmu_common_set_ramp(&led->lmu_data);
		if (ret)
			dev_err(&priv->client->dev, "Setting the ramp rate failed\n");
	}
out:
	return ret;
}