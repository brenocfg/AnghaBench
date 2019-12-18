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
struct TYPE_2__ {int addr; int /*<<< orphan*/  bus; } ;
struct phy_device {int link; int /*<<< orphan*/  attached_dev; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  state; TYPE_1__ mdio; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int MII_BMCR ; 
 int /*<<< orphan*/  PHY_RUNNING ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mdiobus_read (int /*<<< orphan*/ ,int,int) ; 
 int mdiobus_write (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip175c_config_init(struct phy_device *phydev)
{
	int err, i;
	static int full_reset_performed;

	if (full_reset_performed == 0) {

		/* master reset */
		err = mdiobus_write(phydev->mdio.bus, 30, 0, 0x175c);
		if (err < 0)
			return err;

		/* ensure no bus delays overlap reset period */
		err = mdiobus_read(phydev->mdio.bus, 30, 0);

		/* data sheet specifies reset period is 2 msec */
		mdelay(2);

		/* enable IP175C mode */
		err = mdiobus_write(phydev->mdio.bus, 29, 31, 0x175c);
		if (err < 0)
			return err;

		/* Set MII0 speed and duplex (in PHY mode) */
		err = mdiobus_write(phydev->mdio.bus, 29, 22, 0x420);
		if (err < 0)
			return err;

		/* reset switch ports */
		for (i = 0; i < 5; i++) {
			err = mdiobus_write(phydev->mdio.bus, i,
					    MII_BMCR, BMCR_RESET);
			if (err < 0)
				return err;
		}

		for (i = 0; i < 5; i++)
			err = mdiobus_read(phydev->mdio.bus, i, MII_BMCR);

		mdelay(2);

		full_reset_performed = 1;
	}

	if (phydev->mdio.addr != 4) {
		phydev->state = PHY_RUNNING;
		phydev->speed = SPEED_100;
		phydev->duplex = DUPLEX_FULL;
		phydev->link = 1;
		netif_carrier_on(phydev->attached_dev);
	}

	return 0;
}