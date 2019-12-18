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
struct of_phandle_args {scalar_t__ args_count; } ;
struct gpio_desc {int dummy; } ;
struct gpio_chip {scalar_t__ of_gpio_n_cells; int (* of_xlate ) (struct gpio_chip*,struct of_phandle_args*,int*) ;} ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 int EINVAL ; 
 struct gpio_desc* ERR_PTR (int) ; 
 struct gpio_desc* gpiochip_get_desc (struct gpio_chip*,int) ; 
 int stub1 (struct gpio_chip*,struct of_phandle_args*,int*) ; 

__attribute__((used)) static struct gpio_desc *of_xlate_and_get_gpiod_flags(struct gpio_chip *chip,
					struct of_phandle_args *gpiospec,
					enum of_gpio_flags *flags)
{
	int ret;

	if (chip->of_gpio_n_cells != gpiospec->args_count)
		return ERR_PTR(-EINVAL);

	ret = chip->of_xlate(chip, gpiospec, flags);
	if (ret < 0)
		return ERR_PTR(ret);

	return gpiochip_get_desc(chip, ret);
}