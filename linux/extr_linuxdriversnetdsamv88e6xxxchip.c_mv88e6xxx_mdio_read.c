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
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; TYPE_2__* info; } ;
struct mii_bus {struct mv88e6xxx_mdio_bus* priv; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* phy_read ) (struct mv88e6xxx_chip*,struct mii_bus*,int,int,int*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MII_PHYSID2 ; 
 int MV88E6XXX_PORT_SWITCH_ID_PROD_6390 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mv88e6xxx_chip*,struct mii_bus*,int,int,int*) ; 

__attribute__((used)) static int mv88e6xxx_mdio_read(struct mii_bus *bus, int phy, int reg)
{
	struct mv88e6xxx_mdio_bus *mdio_bus = bus->priv;
	struct mv88e6xxx_chip *chip = mdio_bus->chip;
	u16 val;
	int err;

	if (!chip->info->ops->phy_read)
		return -EOPNOTSUPP;

	mutex_lock(&chip->reg_lock);
	err = chip->info->ops->phy_read(chip, bus, phy, reg, &val);
	mutex_unlock(&chip->reg_lock);

	if (reg == MII_PHYSID2) {
		/* Some internal PHYS don't have a model number.  Use
		 * the mv88e6390 family model number instead.
		 */
		if (!(val & 0x3f0))
			val |= MV88E6XXX_PORT_SWITCH_ID_PROD_6390 >> 4;
	}

	return err ? err : val;
}