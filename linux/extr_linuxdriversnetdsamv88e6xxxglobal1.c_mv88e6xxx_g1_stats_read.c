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
typedef  int u32 ;
typedef  int u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_G1_STATS_COUNTER_01 ; 
 int /*<<< orphan*/  MV88E6XXX_G1_STATS_COUNTER_32 ; 
 int /*<<< orphan*/  MV88E6XXX_G1_STATS_OP ; 
 int MV88E6XXX_G1_STATS_OP_BUSY ; 
 int MV88E6XXX_G1_STATS_OP_READ_CAPTURED ; 
 int mv88e6xxx_g1_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_g1_stats_wait (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

void mv88e6xxx_g1_stats_read(struct mv88e6xxx_chip *chip, int stat, u32 *val)
{
	u32 value;
	u16 reg;
	int err;

	*val = 0;

	err = mv88e6xxx_g1_write(chip, MV88E6XXX_G1_STATS_OP,
				 MV88E6XXX_G1_STATS_OP_BUSY |
				 MV88E6XXX_G1_STATS_OP_READ_CAPTURED | stat);
	if (err)
		return;

	err = mv88e6xxx_g1_stats_wait(chip);
	if (err)
		return;

	err = mv88e6xxx_g1_read(chip, MV88E6XXX_G1_STATS_COUNTER_32, &reg);
	if (err)
		return;

	value = reg << 16;

	err = mv88e6xxx_g1_read(chip, MV88E6XXX_G1_STATS_COUNTER_01, &reg);
	if (err)
		return;

	*val = value | reg;
}