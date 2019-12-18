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
struct ssb_bus {int /*<<< orphan*/  extif; int /*<<< orphan*/  chipco; } ;

/* Variables and functions */
 scalar_t__ ssb_chipco_available (int /*<<< orphan*/ *) ; 
 scalar_t__ ssb_extif_available (int /*<<< orphan*/ *) ; 
 int ssb_gpio_chipco_init (struct ssb_bus*) ; 
 int ssb_gpio_extif_init (struct ssb_bus*) ; 

int ssb_gpio_init(struct ssb_bus *bus)
{
	if (ssb_chipco_available(&bus->chipco))
		return ssb_gpio_chipco_init(bus);
	else if (ssb_extif_available(&bus->extif))
		return ssb_gpio_extif_init(bus);
	return -1;
}