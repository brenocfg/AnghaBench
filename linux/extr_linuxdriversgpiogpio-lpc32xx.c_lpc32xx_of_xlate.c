#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct of_phandle_args {size_t* args; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_3__ {struct gpio_chip chip; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* lpc32xx_gpiochip ; 

__attribute__((used)) static int lpc32xx_of_xlate(struct gpio_chip *gc,
			    const struct of_phandle_args *gpiospec, u32 *flags)
{
	/* Is this the correct bank? */
	u32 bank = gpiospec->args[0];
	if ((bank >= ARRAY_SIZE(lpc32xx_gpiochip) ||
	    (gc != &lpc32xx_gpiochip[bank].chip)))
		return -EINVAL;

	if (flags)
		*flags = gpiospec->args[2];
	return gpiospec->args[1];
}