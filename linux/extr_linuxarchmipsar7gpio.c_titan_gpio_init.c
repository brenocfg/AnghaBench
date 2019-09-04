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
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar7_gpio_enable_titan (unsigned int) ; 
 TYPE_1__ titan_gpio_chip ; 
 int /*<<< orphan*/  titan_gpio_direction_input (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  titan_gpio_pinsel (unsigned int) ; 

__attribute__((used)) static void titan_gpio_init(void)
{
	unsigned i;

	for (i = 44; i < 48; i++) {
		titan_gpio_pinsel(i);
		ar7_gpio_enable_titan(i);
		titan_gpio_direction_input(&titan_gpio_chip.chip, i);
	}
}