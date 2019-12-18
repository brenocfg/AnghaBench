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
typedef  int u32 ;
struct of_phandle_args {int* args; } ;
struct gpio_chip {int of_gpio_n_cells; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int pm8xxx_mpp_of_xlate(struct gpio_chip *chip,
				const struct of_phandle_args *gpio_desc,
				u32 *flags)
{
	if (chip->of_gpio_n_cells < 2)
		return -EINVAL;

	if (flags)
		*flags = gpio_desc->args[1];

	return gpio_desc->args[0] - 1;
}