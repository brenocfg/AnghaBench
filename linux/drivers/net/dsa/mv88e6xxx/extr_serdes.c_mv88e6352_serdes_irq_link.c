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
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  dsa_port_phylink_mac_change (struct dsa_switch*,int,int) ; 
 int mv88e6352_serdes_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void mv88e6352_serdes_irq_link(struct mv88e6xxx_chip *chip, int port)
{
	struct dsa_switch *ds = chip->ds;
	u16 status;
	bool up;
	int err;

	err = mv88e6352_serdes_read(chip, MII_BMSR, &status);
	if (err)
		return;

	/* Status must be read twice in order to give the current link
	 * status. Otherwise the change in link status since the last
	 * read of the register is returned.
	 */
	err = mv88e6352_serdes_read(chip, MII_BMSR, &status);
	if (err)
		return;

	up = status & BMSR_LSTATUS;

	dsa_port_phylink_mac_change(ds, port, up);
}