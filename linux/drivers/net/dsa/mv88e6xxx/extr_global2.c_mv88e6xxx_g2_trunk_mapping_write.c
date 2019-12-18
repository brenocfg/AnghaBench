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
typedef  int const u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MV88E6XXX_G2_TRUNK_MAPPING ; 
 int const MV88E6XXX_G2_TRUNK_MAPPING_UPDATE ; 
 int mv88e6xxx_g2_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_g2_trunk_mapping_write(struct mv88e6xxx_chip *chip, int id,
					    u16 map)
{
	const u16 port_mask = BIT(mv88e6xxx_num_ports(chip)) - 1;
	u16 val = (id << 11) | (map & port_mask);

	return mv88e6xxx_g2_write(chip, MV88E6XXX_G2_TRUNK_MAPPING,
				  MV88E6XXX_G2_TRUNK_MAPPING_UPDATE | val);
}