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
struct gpio_desc {char const* label; int /*<<< orphan*/  flags; } ;
struct gpio_chip {unsigned int ngpio; TYPE_1__* gpiodev; } ;
struct TYPE_2__ {struct gpio_desc* descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_REQUESTED ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *gpiochip_is_requested(struct gpio_chip *chip, unsigned offset)
{
	struct gpio_desc *desc;

	if (offset >= chip->ngpio)
		return NULL;

	desc = &chip->gpiodev->descs[offset];

	if (test_bit(FLAG_REQUESTED, &desc->flags) == 0)
		return NULL;
	return desc->label;
}