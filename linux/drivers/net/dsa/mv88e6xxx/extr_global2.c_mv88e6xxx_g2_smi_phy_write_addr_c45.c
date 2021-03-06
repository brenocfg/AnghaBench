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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WRITE_ADDR ; 
 int /*<<< orphan*/  MV88E6XXX_G2_SMI_PHY_DATA ; 
 int mv88e6xxx_g2_smi_phy_access_c45 (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int,int) ; 
 int mv88e6xxx_g2_smi_phy_wait (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g2_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6xxx_g2_smi_phy_write_addr_c45(struct mv88e6xxx_chip *chip,
					       bool external, int port, int dev,
					       int addr)
{
	u16 op = MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WRITE_ADDR;
	int err;

	err = mv88e6xxx_g2_smi_phy_wait(chip);
	if (err)
		return err;

	err = mv88e6xxx_g2_write(chip, MV88E6XXX_G2_SMI_PHY_DATA, addr);
	if (err)
		return err;

	return mv88e6xxx_g2_smi_phy_access_c45(chip, external, op, port, dev);
}