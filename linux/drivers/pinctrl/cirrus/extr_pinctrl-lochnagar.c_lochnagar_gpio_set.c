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
struct lochnagar_pin_priv {int /*<<< orphan*/  dev; TYPE_1__* pins; struct lochnagar* lochnagar; } ;
struct lochnagar_pin {int type; int shift; int /*<<< orphan*/  name; int /*<<< orphan*/  reg; int /*<<< orphan*/  invert; } ;
struct lochnagar {int /*<<< orphan*/  regmap; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {struct lochnagar_pin* drv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int LN2_OP_GPIO ; 
#define  LN_PTYPE_GPIO 129 
#define  LN_PTYPE_MUX 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct lochnagar_pin_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int lochnagar_pin_set_mux (struct lochnagar_pin_priv*,struct lochnagar_pin const*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lochnagar_gpio_set(struct gpio_chip *chip,
			       unsigned int offset, int value)
{
	struct lochnagar_pin_priv *priv = gpiochip_get_data(chip);
	struct lochnagar *lochnagar = priv->lochnagar;
	const struct lochnagar_pin *pin = priv->pins[offset].drv_data;
	int ret;

	value = !!value;

	dev_dbg(priv->dev, "Set GPIO %s to %s\n",
		pin->name, value ? "high" : "low");

	switch (pin->type) {
	case LN_PTYPE_MUX:
		value |= LN2_OP_GPIO;

		ret = lochnagar_pin_set_mux(priv, pin, value);
		break;
	case LN_PTYPE_GPIO:
		if (pin->invert)
			value = !value;

		ret = regmap_update_bits(lochnagar->regmap, pin->reg,
					 BIT(pin->shift), value << pin->shift);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret < 0)
		dev_err(chip->parent, "Failed to set %s value: %d\n",
			pin->name, ret);
}