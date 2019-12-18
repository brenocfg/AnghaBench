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
struct TYPE_2__ {unsigned int base; unsigned int ngpio; } ;
struct nmk_gpio_chip {TYPE_1__ chip; } ;

/* Variables and functions */
 int NMK_MAX_BANKS ; 
 struct nmk_gpio_chip** nmk_gpio_chips ; 

__attribute__((used)) static struct nmk_gpio_chip *find_nmk_gpio_from_pin(unsigned pin)
{
	int i;
	struct nmk_gpio_chip *nmk_gpio;

	for(i = 0; i < NMK_MAX_BANKS; i++) {
		nmk_gpio = nmk_gpio_chips[i];
		if (!nmk_gpio)
			continue;
		if (pin >= nmk_gpio->chip.base &&
			pin < nmk_gpio->chip.base + nmk_gpio->chip.ngpio)
			return nmk_gpio;
	}
	return NULL;
}