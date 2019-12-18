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
struct wmt_pinctrl_data {size_t base; TYPE_1__* banks; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {size_t reg_dir; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 size_t WMT_BANK_FROM_PIN (unsigned int) ; 
 size_t WMT_BIT_FROM_PIN (unsigned int) ; 
 struct wmt_pinctrl_data* gpiochip_get_data (struct gpio_chip*) ; 
 size_t readl_relaxed (size_t) ; 

__attribute__((used)) static int wmt_gpio_get_direction(struct gpio_chip *chip, unsigned offset)
{
	struct wmt_pinctrl_data *data = gpiochip_get_data(chip);
	u32 bank = WMT_BANK_FROM_PIN(offset);
	u32 bit = WMT_BIT_FROM_PIN(offset);
	u32 reg_dir = data->banks[bank].reg_dir;
	u32 val;

	val = readl_relaxed(data->base + reg_dir);
	/* Return 0 == output, 1 == input */
	return !(val & BIT(bit));
}