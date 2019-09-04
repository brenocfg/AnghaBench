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

/* Variables and functions */
 int /*<<< orphan*/  alchemy_gpio_set_value (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mtx1_pci_idsel(unsigned int devsel, int assert)
{
	/* This function is only necessary to support a proprietary Cardbus
	 * adapter on the mtx-1 "singleboard" variant. It triggers a custom
	 * logic chip connected to EXT_IO3 (GPIO1) to suppress IDSEL signals.
	 */
	udelay(1);

	if (assert && devsel != 0)
		/* Suppress signal to Cardbus */
		alchemy_gpio_set_value(1, 0);	/* set EXT_IO3 OFF */
	else
		alchemy_gpio_set_value(1, 1);	/* set EXT_IO3 ON */

	udelay(1);
	return 1;
}