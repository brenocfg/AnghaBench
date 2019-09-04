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
 scalar_t__ mv88e6352_port_has_serdes (struct mv88e6xxx_chip*,int) ; 
 int mv88e6352_serdes_power_set (struct mv88e6xxx_chip*,int) ; 

int mv88e6352_serdes_power(struct mv88e6xxx_chip *chip, int port, bool on)
{
	int err;

	if (mv88e6352_port_has_serdes(chip, port)) {
		err = mv88e6352_serdes_power_set(chip, on);
		if (err < 0)
			return err;
	}

	return 0;
}