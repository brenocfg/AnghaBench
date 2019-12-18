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
typedef  int u16 ;
struct mv88e6xxx_mdio_bus {struct mv88e6xxx_chip* chip; } ;
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct mii_bus {struct mv88e6xxx_mdio_bus* priv; } ;
struct TYPE_4__ {int (* phy_read ) (struct mv88e6xxx_chip*,struct mii_bus*,int,int,int*) ;} ;
struct TYPE_3__ {scalar_t__ family; TYPE_2__* ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MII_PHYSID2 ; 
 scalar_t__ MV88E6XXX_FAMILY_6165 ; 
 int MV88E6XXX_PORT_SWITCH_ID_PROD_6390 ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int stub1 (struct mv88e6xxx_chip*,struct mii_bus*,int,int,int*) ; 

__attribute__((used)) static int mv88e6xxx_mdio_read(struct mii_bus *bus, int phy, int reg)
{
	struct mv88e6xxx_mdio_bus *mdio_bus = bus->priv;
	struct mv88e6xxx_chip *chip = mdio_bus->chip;
	u16 val;
	int err;

	if (!chip->info->ops->phy_read)
		return -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);
	err = chip->info->ops->phy_read(chip, bus, phy, reg, &val);
	mv88e6xxx_reg_unlock(chip);

	if (reg == MII_PHYSID2) {
		/* Some internal PHYs don't have a model number. */
		if (chip->info->family != MV88E6XXX_FAMILY_6165)
			/* Then there is the 6165 family. It gets is
			 * PHYs correct. But it can also have two
			 * SERDES interfaces in the PHY address
			 * space. And these don't have a model
			 * number. But they are not PHYs, so we don't
			 * want to give them something a PHY driver
			 * will recognise.
			 *
			 * Use the mv88e6390 family model number
			 * instead, for anything which really could be
			 * a PHY,
			 */
			if (!(val & 0x3f0))
				val |= MV88E6XXX_PORT_SWITCH_ID_PROD_6390 >> 4;
	}

	return err ? err : val;
}