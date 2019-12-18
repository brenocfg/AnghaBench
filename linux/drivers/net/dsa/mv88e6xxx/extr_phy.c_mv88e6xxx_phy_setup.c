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
 int mv88e6xxx_phy_ppu_enable (struct mv88e6xxx_chip*) ; 

int mv88e6xxx_phy_setup(struct mv88e6xxx_chip *chip)
{
	return mv88e6xxx_phy_ppu_enable(chip);
}