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
struct hw_factory {int* number_of_pins; int /*<<< orphan*/ * funcs; } ;

/* Variables and functions */
 size_t GPIO_ID_DDC_CLOCK ; 
 size_t GPIO_ID_DDC_DATA ; 
 size_t GPIO_ID_GENERIC ; 
 size_t GPIO_ID_GPIO_PAD ; 
 size_t GPIO_ID_GSL ; 
 size_t GPIO_ID_HPD ; 
 size_t GPIO_ID_SYNC ; 
 size_t GPIO_ID_VIP_PAD ; 
 int /*<<< orphan*/  funcs ; 

void dal_hw_factory_dce120_init(struct hw_factory *factory)
{
	/*TODO check ASIC CAPs*/
	factory->number_of_pins[GPIO_ID_DDC_DATA] = 8;
	factory->number_of_pins[GPIO_ID_DDC_CLOCK] = 8;
	factory->number_of_pins[GPIO_ID_GENERIC] = 7;
	factory->number_of_pins[GPIO_ID_HPD] = 6;
	factory->number_of_pins[GPIO_ID_GPIO_PAD] = 31;
	factory->number_of_pins[GPIO_ID_VIP_PAD] = 0;
	factory->number_of_pins[GPIO_ID_SYNC] = 2;
	factory->number_of_pins[GPIO_ID_GSL] = 4;

	factory->funcs = &funcs;
}