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

/* Variables and functions */
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_port_add_broadcast (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_broadcast_setup(struct mv88e6xxx_chip *chip, u16 vid)
{
	int port;
	int err;

	for (port = 0; port < mv88e6xxx_num_ports(chip); port++) {
		err = mv88e6xxx_port_add_broadcast(chip, port, vid);
		if (err)
			return err;
	}

	return 0;
}