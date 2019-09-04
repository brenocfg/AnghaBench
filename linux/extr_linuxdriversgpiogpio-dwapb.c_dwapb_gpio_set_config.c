#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ PIN_CONFIG_INPUT_DEBOUNCE ; 
 int dwapb_gpio_set_debounce (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinconf_to_config_argument (unsigned long) ; 
 scalar_t__ pinconf_to_config_param (unsigned long) ; 

__attribute__((used)) static int dwapb_gpio_set_config(struct gpio_chip *gc, unsigned offset,
				 unsigned long config)
{
	u32 debounce;

	if (pinconf_to_config_param(config) != PIN_CONFIG_INPUT_DEBOUNCE)
		return -ENOTSUPP;

	debounce = pinconf_to_config_argument(config);
	return dwapb_gpio_set_debounce(gc, offset, debounce);
}