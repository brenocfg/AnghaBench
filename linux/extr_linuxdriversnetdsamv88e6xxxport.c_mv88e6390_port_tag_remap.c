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
 int /*<<< orphan*/  MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_AVB_PCP ; 
 int /*<<< orphan*/  MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_GREEN_PCP ; 
 int /*<<< orphan*/  MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_YELLOW_PCP ; 
 int /*<<< orphan*/  MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_INGRESS_PCP ; 
 int mv88e6xxx_port_ieeepmt_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int,int) ; 

int mv88e6390_port_tag_remap(struct mv88e6xxx_chip *chip, int port)
{
	int err, i;
	u16 table;

	for (i = 0; i <= 7; i++) {
		table = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_INGRESS_PCP;
		err = mv88e6xxx_port_ieeepmt_write(chip, port, table, i,
						   (i | i << 4));
		if (err)
			return err;

		table = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_GREEN_PCP;
		err = mv88e6xxx_port_ieeepmt_write(chip, port, table, i, i);
		if (err)
			return err;

		table = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_YELLOW_PCP;
		err = mv88e6xxx_port_ieeepmt_write(chip, port, table, i, i);
		if (err)
			return err;

		table = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_AVB_PCP;
		err = mv88e6xxx_port_ieeepmt_write(chip, port, table, i, i);
		if (err)
			return err;
	}

	return 0;
}