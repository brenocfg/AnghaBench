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
struct max30102_data {scalar_t__ chip_id; int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX30102_REG_IR_LED_CONFIG ; 
 int /*<<< orphan*/  MAX30102_REG_RED_LED_CONFIG ; 
 int /*<<< orphan*/  MAX30105_REG_GREEN_LED_CONFIG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int max30102_get_current_idx (unsigned int,int*) ; 
 scalar_t__ max30105 ; 
 int of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max30102_led_init(struct max30102_data *data)
{
	struct device *dev = &data->client->dev;
	struct device_node *np = dev->of_node;
	unsigned int val;
	int reg, ret;

	ret = of_property_read_u32(np, "maxim,red-led-current-microamp", &val);
	if (ret) {
		dev_info(dev, "no red-led-current-microamp set\n");

		/* Default to 7 mA RED LED */
		val = 7000;
	}

	ret = max30102_get_current_idx(val, &reg);
	if (ret) {
		dev_err(dev, "invalid RED LED current setting %d\n", val);
		return ret;
	}

	ret = regmap_write(data->regmap, MAX30102_REG_RED_LED_CONFIG, reg);
	if (ret)
		return ret;

	if (data->chip_id == max30105) {
		ret = of_property_read_u32(np,
			"maxim,green-led-current-microamp", &val);
		if (ret) {
			dev_info(dev, "no green-led-current-microamp set\n");

			/* Default to 7 mA green LED */
			val = 7000;
		}

		ret = max30102_get_current_idx(val, &reg);
		if (ret) {
			dev_err(dev, "invalid green LED current setting %d\n",
				val);
			return ret;
		}

		ret = regmap_write(data->regmap, MAX30105_REG_GREEN_LED_CONFIG,
				   reg);
		if (ret)
			return ret;
	}

	ret = of_property_read_u32(np, "maxim,ir-led-current-microamp", &val);
	if (ret) {
		dev_info(dev, "no ir-led-current-microamp set\n");

		/* Default to 7 mA IR LED */
		val = 7000;
	}

	ret = max30102_get_current_idx(val, &reg);
	if (ret) {
		dev_err(dev, "invalid IR LED current setting %d\n", val);
		return ret;
	}

	return regmap_write(data->regmap, MAX30102_REG_IR_LED_CONFIG, reg);
}