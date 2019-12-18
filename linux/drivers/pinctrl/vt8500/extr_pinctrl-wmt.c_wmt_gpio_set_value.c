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
typedef  size_t u32 ;
struct wmt_pinctrl_data {int /*<<< orphan*/  dev; TYPE_1__* banks; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {size_t reg_data_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 size_t NO_REG ; 
 size_t WMT_BANK_FROM_PIN (unsigned int) ; 
 size_t WMT_BIT_FROM_PIN (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct wmt_pinctrl_data* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  wmt_clearbits (struct wmt_pinctrl_data*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmt_setbits (struct wmt_pinctrl_data*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wmt_gpio_set_value(struct gpio_chip *chip, unsigned offset,
			       int val)
{
	struct wmt_pinctrl_data *data = gpiochip_get_data(chip);
	u32 bank = WMT_BANK_FROM_PIN(offset);
	u32 bit = WMT_BIT_FROM_PIN(offset);
	u32 reg_data_out = data->banks[bank].reg_data_out;

	if (reg_data_out == NO_REG) {
		dev_err(data->dev, "no data out register defined\n");
		return;
	}

	if (val)
		wmt_setbits(data, reg_data_out, BIT(bit));
	else
		wmt_clearbits(data, reg_data_out, BIT(bit));
}