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
typedef  int u32 ;
struct mlxreg_led_priv_data {struct mlxreg_core_platform_data* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mlxreg_led_data {int base_color; TYPE_1__ led_cdev; struct mlxreg_core_data* data; struct mlxreg_led_priv_data* data_parent; } ;
struct mlxreg_core_platform_data {int /*<<< orphan*/  regmap; } ;
struct mlxreg_core_data {int mask; scalar_t__ bit; int /*<<< orphan*/  reg; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_FULL ; 
 int LED_OFF ; 
 int MLXREG_LED_OFFSET_BLINK_6HZ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ror32 (int,scalar_t__) ; 

__attribute__((used)) static enum led_brightness
mlxreg_led_get_hw(struct mlxreg_led_data *led_data)
{
	struct mlxreg_led_priv_data *priv = led_data->data_parent;
	struct mlxreg_core_platform_data *led_pdata = priv->pdata;
	struct mlxreg_core_data *data = led_data->data;
	u32 regval;
	int err;

	/*
	 * Each LED is controlled through low or high nibble of the relevant
	 * register byte. Register offset is specified by off parameter.
	 * Parameter vset provides color code: 0x0 for off, 0x5 for solid red,
	 * 0x6 for 3Hz blink red, 0xd for solid green, 0xe for 3Hz blink
	 * green.
	 * Parameter mask specifies which nibble is used for specific LED: mask
	 * 0xf0 - lower nibble is to be used (bits from 0 to 3), mask 0x0f -
	 * higher nibble (bits from 4 to 7).
	 */
	err = regmap_read(led_pdata->regmap, data->reg, &regval);
	if (err < 0) {
		dev_warn(led_data->led_cdev.dev, "Failed to get current brightness, error: %d\n",
			 err);
		/* Assume the LED is OFF */
		return LED_OFF;
	}

	regval = regval & ~data->mask;
	regval = (ror32(data->mask, data->bit) == 0xf0) ? ror32(regval,
		 data->bit) : ror32(regval, data->bit + 4);
	if (regval >= led_data->base_color &&
	    regval <= (led_data->base_color + MLXREG_LED_OFFSET_BLINK_6HZ))
		return LED_FULL;

	return LED_OFF;
}