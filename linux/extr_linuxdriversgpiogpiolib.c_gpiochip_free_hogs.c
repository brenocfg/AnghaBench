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
struct gpio_chip {int ngpio; TYPE_1__* gpiodev; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {TYPE_2__* descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_IS_HOGGED ; 
 int /*<<< orphan*/  gpiochip_free_own_desc (TYPE_2__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpiochip_free_hogs(struct gpio_chip *chip)
{
	int id;

	for (id = 0; id < chip->ngpio; id++) {
		if (test_bit(FLAG_IS_HOGGED, &chip->gpiodev->descs[id].flags))
			gpiochip_free_own_desc(&chip->gpiodev->descs[id]);
	}
}