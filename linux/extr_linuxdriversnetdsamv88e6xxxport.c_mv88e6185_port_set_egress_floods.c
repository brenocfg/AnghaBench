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
 int mv88e6185_port_set_default_forward (struct mv88e6xxx_chip*,int,int) ; 
 int mv88e6185_port_set_forward_unknown (struct mv88e6xxx_chip*,int,int) ; 

int mv88e6185_port_set_egress_floods(struct mv88e6xxx_chip *chip, int port,
				     bool unicast, bool multicast)
{
	int err;

	err = mv88e6185_port_set_forward_unknown(chip, port, unicast);
	if (err)
		return err;

	return mv88e6185_port_set_default_forward(chip, port, multicast);
}