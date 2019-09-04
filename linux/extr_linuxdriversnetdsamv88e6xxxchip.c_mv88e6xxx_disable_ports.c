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
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_port_set_state (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mv88e6xxx_disable_ports(struct mv88e6xxx_chip *chip)
{
	int i, err;

	/* Set all ports to the Disabled state */
	for (i = 0; i < mv88e6xxx_num_ports(chip); i++) {
		err = mv88e6xxx_port_set_state(chip, i, BR_STATE_DISABLED);
		if (err)
			return err;
	}

	/* Wait for transmit queues to drain,
	 * i.e. 2ms for a maximum frame to be transmitted at 10 Mbps.
	 */
	usleep_range(2000, 4000);

	return 0;
}