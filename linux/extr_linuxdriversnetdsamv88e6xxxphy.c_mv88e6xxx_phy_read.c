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
struct mv88e6xxx_chip {TYPE_2__* info; } ;
struct mii_bus {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* phy_read ) (struct mv88e6xxx_chip*,struct mii_bus*,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct mii_bus* mv88e6xxx_default_mdio_bus (struct mv88e6xxx_chip*) ; 
 int stub1 (struct mv88e6xxx_chip*,struct mii_bus*,int,int,int /*<<< orphan*/ *) ; 

int mv88e6xxx_phy_read(struct mv88e6xxx_chip *chip, int phy, int reg, u16 *val)
{
	int addr = phy; /* PHY devices addresses start at 0x0 */
	struct mii_bus *bus;

	bus = mv88e6xxx_default_mdio_bus(chip);
	if (!bus)
		return -EOPNOTSUPP;

	if (!chip->info->ops->phy_read)
		return -EOPNOTSUPP;

	return chip->info->ops->phy_read(chip, bus, addr, reg, val);
}