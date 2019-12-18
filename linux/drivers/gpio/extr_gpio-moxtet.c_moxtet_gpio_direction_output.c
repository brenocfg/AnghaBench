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
struct TYPE_2__ {int out_mask; int in_mask; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 struct moxtet_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  moxtet_gpio_set_value (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int moxtet_gpio_direction_output(struct gpio_chip *gc,
					unsigned int offset, int val)
{
	struct moxtet_gpio_chip *chip = gpiochip_get_data(gc);

	if (chip->desc->out_mask & BIT(offset))
		moxtet_gpio_set_value(gc, offset, val);
	else if (chip->desc->in_mask & BIT(offset))
		return -ENOTSUPP;
	else
		return -EINVAL;

	return 0;
}