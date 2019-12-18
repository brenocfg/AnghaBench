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
 int /*<<< orphan*/  MV88E6352_G2_WDOG_CTL ; 
 int MV88E6352_G2_WDOG_CTL_EGRESS_ENABLE ; 
 int MV88E6352_G2_WDOG_CTL_QC_ENABLE ; 
 int /*<<< orphan*/  mv88e6xxx_g2_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mv88e6xxx_g2_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mv88e6097_watchdog_free(struct mv88e6xxx_chip *chip)
{
	u16 reg;

	mv88e6xxx_g2_read(chip, MV88E6352_G2_WDOG_CTL, &reg);

	reg &= ~(MV88E6352_G2_WDOG_CTL_EGRESS_ENABLE |
		 MV88E6352_G2_WDOG_CTL_QC_ENABLE);

	mv88e6xxx_g2_write(chip, MV88E6352_G2_WDOG_CTL, reg);
}