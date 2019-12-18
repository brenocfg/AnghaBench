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
typedef  size_t u8 ;
struct gpio_chip {int dummy; } ;
struct gb_gpio_controller {TYPE_1__* lines; } ;
struct TYPE_2__ {int value; } ;

/* Variables and functions */
 int gb_gpio_get_value_operation (struct gb_gpio_controller*,size_t) ; 
 struct gb_gpio_controller* gpio_chip_to_gb_gpio_controller (struct gpio_chip*) ; 

__attribute__((used)) static int gb_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	u8 which;
	int ret;

	which = (u8)offset;
	ret = gb_gpio_get_value_operation(ggc, which);
	if (ret)
		return ret;

	return ggc->lines[which].value;
}