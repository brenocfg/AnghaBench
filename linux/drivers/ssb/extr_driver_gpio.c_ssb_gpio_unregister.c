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
struct ssb_bus {int /*<<< orphan*/  gpio; int /*<<< orphan*/  extif; int /*<<< orphan*/  chipco; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 scalar_t__ ssb_chipco_available (int /*<<< orphan*/ *) ; 
 scalar_t__ ssb_extif_available (int /*<<< orphan*/ *) ; 

int ssb_gpio_unregister(struct ssb_bus *bus)
{
	if (ssb_chipco_available(&bus->chipco) ||
	    ssb_extif_available(&bus->extif)) {
		gpiochip_remove(&bus->gpio);
		return 0;
	}
	return -1;
}