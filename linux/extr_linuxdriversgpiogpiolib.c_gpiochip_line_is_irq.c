#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {unsigned int ngpio; TYPE_2__* gpiodev; } ;
struct TYPE_4__ {TYPE_1__* descs; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_USED_AS_IRQ ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool gpiochip_line_is_irq(struct gpio_chip *chip, unsigned int offset)
{
	if (offset >= chip->ngpio)
		return false;

	return test_bit(FLAG_USED_AS_IRQ, &chip->gpiodev->descs[offset].flags);
}