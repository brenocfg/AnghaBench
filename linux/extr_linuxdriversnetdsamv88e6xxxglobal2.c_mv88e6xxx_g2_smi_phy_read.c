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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_mdio_bus {int external; } ;
struct mv88e6xxx_chip {int dummy; } ;
struct mii_bus {struct mv88e6xxx_mdio_bus* priv; } ;

/* Variables and functions */
 int MII_ADDR_C45 ; 
 int mv88e6xxx_g2_smi_phy_read_c45 (struct mv88e6xxx_chip*,int,int,int,int /*<<< orphan*/ *) ; 
 int mv88e6xxx_g2_smi_phy_read_data_c22 (struct mv88e6xxx_chip*,int,int,int,int /*<<< orphan*/ *) ; 

int mv88e6xxx_g2_smi_phy_read(struct mv88e6xxx_chip *chip, struct mii_bus *bus,
			      int addr, int reg, u16 *val)
{
	struct mv88e6xxx_mdio_bus *mdio_bus = bus->priv;
	bool external = mdio_bus->external;

	if (reg & MII_ADDR_C45)
		return mv88e6xxx_g2_smi_phy_read_c45(chip, external, addr, reg,
						     val);

	return mv88e6xxx_g2_smi_phy_read_data_c22(chip, external, addr, reg,
						  val);
}