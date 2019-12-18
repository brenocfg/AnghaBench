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
 int /*<<< orphan*/  MV88E6390_G2_WDOG_CTL ; 
 int MV88E6390_G2_WDOG_CTL_CUT_THROUGH ; 
 int MV88E6390_G2_WDOG_CTL_EGRESS ; 
 int MV88E6390_G2_WDOG_CTL_FORCE_IRQ ; 
 int MV88E6390_G2_WDOG_CTL_PTR_INT_ENABLE ; 
 int MV88E6390_G2_WDOG_CTL_QUEUE_CONTROLLER ; 
 int MV88E6390_G2_WDOG_CTL_UPDATE ; 
 int mv88e6xxx_g2_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e6390_watchdog_setup(struct mv88e6xxx_chip *chip)
{
	return mv88e6xxx_g2_write(chip, MV88E6390_G2_WDOG_CTL,
				  MV88E6390_G2_WDOG_CTL_UPDATE |
				  MV88E6390_G2_WDOG_CTL_PTR_INT_ENABLE |
				  MV88E6390_G2_WDOG_CTL_CUT_THROUGH |
				  MV88E6390_G2_WDOG_CTL_QUEUE_CONTROLLER |
				  MV88E6390_G2_WDOG_CTL_EGRESS |
				  MV88E6390_G2_WDOG_CTL_FORCE_IRQ);
}