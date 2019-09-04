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
typedef  int u16 ;
struct mv88e6xxx_chip {struct dsa_switch* ds; } ;
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  MV88E6390_SGMII_STATUS ; 
 int MV88E6390_SGMII_STATUS_LINK ; 
 int /*<<< orphan*/  dsa_port_phylink_mac_change (struct dsa_switch*,int,int) ; 
 int /*<<< orphan*/  mv88e6390_serdes_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void mv88e6390_serdes_irq_link_sgmii(struct mv88e6xxx_chip *chip,
					    int port, int lane)
{
	struct dsa_switch *ds = chip->ds;
	u16 status;
	bool up;

	mv88e6390_serdes_read(chip, lane, MDIO_MMD_PHYXS,
			      MV88E6390_SGMII_STATUS, &status);

	/* Status must be read twice in order to give the current link
	 * status. Otherwise the change in link status since the last
	 * read of the register is returned.
	 */
	mv88e6390_serdes_read(chip, lane, MDIO_MMD_PHYXS,
			      MV88E6390_SGMII_STATUS, &status);
	up = status & MV88E6390_SGMII_STATUS_LINK;

	dsa_port_phylink_mac_change(ds, port, up);
}