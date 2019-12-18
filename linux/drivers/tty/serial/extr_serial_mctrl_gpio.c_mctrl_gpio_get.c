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
struct mctrl_gpios {scalar_t__* gpio; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;
struct TYPE_2__ {unsigned int mctrl; } ;

/* Variables and functions */
 int UART_GPIO_MAX ; 
 scalar_t__ gpiod_get_value (scalar_t__) ; 
 int /*<<< orphan*/  mctrl_gpio_flags_is_dir_out (int) ; 
 TYPE_1__* mctrl_gpios_desc ; 

unsigned int mctrl_gpio_get(struct mctrl_gpios *gpios, unsigned int *mctrl)
{
	enum mctrl_gpio_idx i;

	if (gpios == NULL)
		return *mctrl;

	for (i = 0; i < UART_GPIO_MAX; i++) {
		if (gpios->gpio[i] && !mctrl_gpio_flags_is_dir_out(i)) {
			if (gpiod_get_value(gpios->gpio[i]))
				*mctrl |= mctrl_gpios_desc[i].mctrl;
			else
				*mctrl &= ~mctrl_gpios_desc[i].mctrl;
		}
	}

	return *mctrl;
}