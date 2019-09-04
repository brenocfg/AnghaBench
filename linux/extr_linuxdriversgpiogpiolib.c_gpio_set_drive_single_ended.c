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
 int /*<<< orphan*/  PIN_CONF_PACKED (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct gpio_chip*,unsigned int,unsigned long) ; 

__attribute__((used)) static int gpio_set_drive_single_ended(struct gpio_chip *gc, unsigned offset,
				       enum pin_config_param mode)
{
	unsigned long config = { PIN_CONF_PACKED(mode, 0) };

	return gc->set_config ? gc->set_config(gc, offset, config) : -ENOTSUPP;
}