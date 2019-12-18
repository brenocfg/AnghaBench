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
struct ssb_bus {int powered_up; int /*<<< orphan*/  chipco; } ;
typedef  enum ssb_clkmode { ____Placeholder_ssb_clkmode } ssb_clkmode ;

/* Variables and functions */
 int SSB_CLKMODE_DYNAMIC ; 
 int SSB_CLKMODE_FAST ; 
 int SSB_GPIO_PLL ; 
 int SSB_GPIO_XTAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  ssb_chipco_set_clockmode (int /*<<< orphan*/ *,int) ; 
 int ssb_pci_xtal (struct ssb_bus*,int,int) ; 

int ssb_bus_powerup(struct ssb_bus *bus, bool dynamic_pctl)
{
	int err;
	enum ssb_clkmode mode;

	err = ssb_pci_xtal(bus, SSB_GPIO_XTAL | SSB_GPIO_PLL, 1);
	if (err)
		goto error;

	bus->powered_up = 1;

	mode = dynamic_pctl ? SSB_CLKMODE_DYNAMIC : SSB_CLKMODE_FAST;
	ssb_chipco_set_clockmode(&bus->chipco, mode);

	return 0;
error:
	pr_err("Bus powerup failed\n");
	return err;
}