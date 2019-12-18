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
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_BASE_VLAN ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int mv88e6xxx_num_databases (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

int mv88e6xxx_port_set_fid(struct mv88e6xxx_chip *chip, int port, u16 fid)
{
	const u16 upper_mask = (mv88e6xxx_num_databases(chip) - 1) >> 4;
	u16 reg;
	int err;

	if (fid >= mv88e6xxx_num_databases(chip))
		return -EINVAL;

	/* Port's default FID lower 4 bits are located in reg 0x06, offset 12 */
	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_BASE_VLAN, &reg);
	if (err)
		return err;

	reg &= 0x0fff;
	reg |= (fid & 0x000f) << 12;

	err = mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_BASE_VLAN, reg);
	if (err)
		return err;

	/* Port's default FID upper bits are located in reg 0x05, offset 0 */
	if (upper_mask) {
		err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_CTL1,
					  &reg);
		if (err)
			return err;

		reg &= ~upper_mask;
		reg |= (fid >> 4) & upper_mask;

		err = mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_CTL1,
					   reg);
		if (err)
			return err;
	}

	dev_dbg(chip->dev, "p%d: FID set to %u\n", port, fid);

	return 0;
}