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
struct lm3532_led {scalar_t__ enabled; TYPE_1__* priv; int /*<<< orphan*/  control_bank; } ;
struct TYPE_2__ {int /*<<< orphan*/  regulator; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM3532_REG_ENABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3532_led_disable(struct lm3532_led *led_data)
{
	int ctrl_en_val = BIT(led_data->control_bank);
	int ret;

	if (!led_data->enabled)
		return 0;

	ret = regmap_update_bits(led_data->priv->regmap, LM3532_REG_ENABLE,
					 ctrl_en_val, 0);
	if (ret) {
		dev_err(led_data->priv->dev, "Failed to set ctrl:%d\n", ret);
		return ret;
	}

	ret = regulator_disable(led_data->priv->regulator);
	if (ret < 0)
		return ret;

	led_data->enabled = 0;

	return 0;
}