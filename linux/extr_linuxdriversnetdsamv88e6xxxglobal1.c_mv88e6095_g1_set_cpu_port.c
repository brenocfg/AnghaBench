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
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6185_G1_MONITOR_CTL ; 
 int MV88E6185_G1_MONITOR_CTL_ARP_DEST_MASK ; 
 int __bf_shf (int) ; 
 int mv88e6xxx_g1_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 int mv88e6xxx_g1_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6095_g1_set_cpu_port(struct mv88e6xxx_chip *chip, int port)
{
	u16 reg;
	int err;

	err = mv88e6xxx_g1_read(chip, MV88E6185_G1_MONITOR_CTL, &reg);
	if (err)
		return err;

	reg &= ~MV88E6185_G1_MONITOR_CTL_ARP_DEST_MASK;
	reg |= port << __bf_shf(MV88E6185_G1_MONITOR_CTL_ARP_DEST_MASK);

	return mv88e6xxx_g1_write(chip, MV88E6185_G1_MONITOR_CTL, reg);
}