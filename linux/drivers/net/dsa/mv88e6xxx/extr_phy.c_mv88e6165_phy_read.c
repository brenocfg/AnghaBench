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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int mv88e6xxx_read (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ *) ; 

int mv88e6165_phy_read(struct mv88e6xxx_chip *chip, struct mii_bus *bus,
		       int addr, int reg, u16 *val)
{
	return mv88e6xxx_read(chip, addr, reg, val);
}