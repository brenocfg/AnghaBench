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
 int /*<<< orphan*/  MV88E6390_G2_WDOG_CTL_PTR_INT_ENABLE ; 
 int /*<<< orphan*/  mv88e6xxx_g2_update (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv88e6390_watchdog_free(struct mv88e6xxx_chip *chip)
{
	mv88e6xxx_g2_update(chip, MV88E6390_G2_WDOG_CTL,
			    MV88E6390_G2_WDOG_CTL_PTR_INT_ENABLE);
}