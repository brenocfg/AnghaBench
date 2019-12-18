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
struct TYPE_2__ {int addr; } ;
struct phy_device {int /*<<< orphan*/  irq; TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_IGNORE_INTERRUPT ; 
 int /*<<< orphan*/  genphy_read_status (struct phy_device*) ; 

__attribute__((used)) static int ip175c_read_status(struct phy_device *phydev)
{
	if (phydev->mdio.addr == 4) /* WAN port */
		genphy_read_status(phydev);
	else
		/* Don't need to read status for switch ports */
		phydev->irq = PHY_IGNORE_INTERRUPT;

	return 0;
}