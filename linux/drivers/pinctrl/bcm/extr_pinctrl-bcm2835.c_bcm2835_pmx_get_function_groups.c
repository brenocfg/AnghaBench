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
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 char** bcm2835_gpio_groups ; 

__attribute__((used)) static int bcm2835_pmx_get_function_groups(struct pinctrl_dev *pctldev,
		unsigned selector,
		const char * const **groups,
		unsigned * const num_groups)
{
	/* every pin can do every function */
	*groups = bcm2835_gpio_groups;
	*num_groups = ARRAY_SIZE(bcm2835_gpio_groups);

	return 0;
}