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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int MV88E6XXX_MAX_PVT_PORTS ; 
 int MV88E6XXX_MAX_PVT_SWITCHES ; 
 int mv88e6xxx_g2_misc_4_bit_port (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_has_pvt (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_pvt_map (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static int mv88e6xxx_pvt_setup(struct mv88e6xxx_chip *chip)
{
	int dev, port;
	int err;

	if (!mv88e6xxx_has_pvt(chip))
		return 0;

	/* Clear 5 Bit Port for usage with Marvell Link Street devices:
	 * use 4 bits for the Src_Port/Src_Trunk and 5 bits for the Src_Dev.
	 */
	err = mv88e6xxx_g2_misc_4_bit_port(chip);
	if (err)
		return err;

	for (dev = 0; dev < MV88E6XXX_MAX_PVT_SWITCHES; ++dev) {
		for (port = 0; port < MV88E6XXX_MAX_PVT_PORTS; ++port) {
			err = mv88e6xxx_pvt_map(chip, dev, port);
			if (err)
				return err;
		}
	}

	return 0;
}