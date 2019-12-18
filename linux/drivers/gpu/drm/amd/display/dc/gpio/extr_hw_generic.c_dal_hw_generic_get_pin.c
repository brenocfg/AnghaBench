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
struct hw_gpio_pin {int dummy; } ;
struct TYPE_2__ {struct hw_gpio_pin base; } ;
struct hw_generic {TYPE_1__ base; } ;
struct gpio {int dummy; } ;

/* Variables and functions */
 struct hw_generic* dal_gpio_get_generic (struct gpio*) ; 

struct hw_gpio_pin *dal_hw_generic_get_pin(struct gpio *gpio)
{
	struct hw_generic *hw_generic = dal_gpio_get_generic(gpio);

	return &hw_generic->base.base;
}