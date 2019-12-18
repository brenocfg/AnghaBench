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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_mdio_bus {struct mv88e6xxx_chip* chip; } ;
struct mv88e6xxx_chip {TYPE_2__* info; } ;
struct mii_bus {struct mv88e6xxx_mdio_bus* priv; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* phy_write ) (struct mv88e6xxx_chip*,struct mii_bus*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int stub1 (struct mv88e6xxx_chip*,struct mii_bus*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_mdio_write(struct mii_bus *bus, int phy, int reg, u16 val)
{
	struct mv88e6xxx_mdio_bus *mdio_bus = bus->priv;
	struct mv88e6xxx_chip *chip = mdio_bus->chip;
	int err;

	if (!chip->info->ops->phy_write)
		return -EOPNOTSUPP;

	mv88e6xxx_reg_lock(chip);
	err = chip->info->ops->phy_write(chip, bus, phy, reg, val);
	mv88e6xxx_reg_unlock(chip);

	return err;
}