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
struct moxtet_gpio_chip {TYPE_1__* desc; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int in_mask; int out_mask; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 struct moxtet_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int moxtet_gpio_direction_input(struct gpio_chip *gc,
				       unsigned int offset)
{
	struct moxtet_gpio_chip *chip = gpiochip_get_data(gc);

	if (chip->desc->in_mask & BIT(offset))
		return 0;
	else if (chip->desc->out_mask & BIT(offset))
		return -ENOTSUPP;
	else
		return -EINVAL;
}