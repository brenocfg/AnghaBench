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
 int /*<<< orphan*/  BR_STATE_DISABLED ; 
 scalar_t__ mv88e6390_setup_errata_applied (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_port_hidden_write (struct mv88e6xxx_chip*,int,int,int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_port_set_state (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_software_reset (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6390_setup_errata(struct mv88e6xxx_chip *chip)
{
	int port;
	int err;

	if (mv88e6390_setup_errata_applied(chip))
		return 0;

	/* Set the ports into blocking mode */
	for (port = 0; port < mv88e6xxx_num_ports(chip); port++) {
		err = mv88e6xxx_port_set_state(chip, port, BR_STATE_DISABLED);
		if (err)
			return err;
	}

	for (port = 0; port < mv88e6xxx_num_ports(chip); port++) {
		err = mv88e6xxx_port_hidden_write(chip, 0xf, port, 0, 0x01c0);
		if (err)
			return err;
	}

	return mv88e6xxx_software_reset(chip);
}