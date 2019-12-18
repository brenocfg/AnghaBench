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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PHY_MAX_ADDR ; 
 int moxart_mdio_read (struct mii_bus*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ moxart_mdio_write (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int moxart_mdio_reset(struct mii_bus *bus)
{
	int data, i;

	for (i = 0; i < PHY_MAX_ADDR; i++) {
		data = moxart_mdio_read(bus, i, MII_BMCR);
		if (data < 0)
			continue;

		data |= BMCR_RESET;
		if (moxart_mdio_write(bus, i, MII_BMCR, data) < 0)
			continue;
	}

	return 0;
}