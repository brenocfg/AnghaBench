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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int BMCR_PDOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int mv88e6352_serdes_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 int mv88e6352_serdes_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6352_serdes_power(struct mv88e6xxx_chip *chip, int port, u8 lane,
			   bool up)
{
	u16 val, new_val;
	int err;

	err = mv88e6352_serdes_read(chip, MII_BMCR, &val);
	if (err)
		return err;

	if (up)
		new_val = val & ~BMCR_PDOWN;
	else
		new_val = val | BMCR_PDOWN;

	if (val != new_val)
		err = mv88e6352_serdes_write(chip, MII_BMCR, new_val);

	return err;
}