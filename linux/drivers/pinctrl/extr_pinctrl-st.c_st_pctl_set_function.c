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
struct st_pio_control {struct regmap_field* alt; } ;
struct regmap_field {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_field_read (struct regmap_field*,unsigned int*) ; 
 int /*<<< orphan*/  regmap_field_write (struct regmap_field*,unsigned int) ; 
 int st_gpio_pin (int) ; 

__attribute__((used)) static void st_pctl_set_function(struct st_pio_control *pc,
				int pin_id, int function)
{
	struct regmap_field *alt = pc->alt;
	unsigned int val;
	int pin = st_gpio_pin(pin_id);
	int offset = pin * 4;

	if (!alt)
		return;

	regmap_field_read(alt, &val);
	val &= ~(0xf << offset);
	val |= function << offset;
	regmap_field_write(alt, val);
}