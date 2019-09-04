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
typedef  int u8 ;
typedef  int u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6390_PORT_IEEE_PRIO_MAP_TABLE ; 
 int MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_DATA_MASK ; 
 int /*<<< orphan*/  MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_PTR_MASK ; 
 int MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_UPDATE ; 
 int __bf_shf (int /*<<< orphan*/ ) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6xxx_port_ieeepmt_write(struct mv88e6xxx_chip *chip,
					int port, u16 table, u8 ptr, u16 data)
{
	u16 reg;

	reg = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_UPDATE | table |
		(ptr << __bf_shf(MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_PTR_MASK)) |
		(data & MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_DATA_MASK);

	return mv88e6xxx_port_write(chip, port,
				    MV88E6390_PORT_IEEE_PRIO_MAP_TABLE, reg);
}