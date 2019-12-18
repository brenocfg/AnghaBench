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
struct gpio_chip {int (* set_config ) (struct gpio_chip*,unsigned int,unsigned long) ;} ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_BIAS_PULL_DOWN 129 
#define  PIN_CONFIG_BIAS_PULL_UP 128 
 unsigned long PIN_CONF_PACKED (int,unsigned int) ; 
 int stub1 (struct gpio_chip*,unsigned int,unsigned long) ; 

__attribute__((used)) static int gpio_set_config(struct gpio_chip *gc, unsigned offset,
			   enum pin_config_param mode)
{
	unsigned long config;
	unsigned arg;

	switch (mode) {
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_BIAS_PULL_UP:
		arg = 1;
		break;

	default:
		arg = 0;
	}

	config = PIN_CONF_PACKED(mode, arg);
	return gc->set_config ? gc->set_config(gc, offset, config) : -ENOTSUPP;
}