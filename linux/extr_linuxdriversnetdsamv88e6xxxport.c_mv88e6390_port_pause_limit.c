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
typedef  int u8 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6390_PORT_FLOW_CTL ; 
 int MV88E6390_PORT_FLOW_CTL_LIMIT_IN ; 
 int MV88E6390_PORT_FLOW_CTL_LIMIT_OUT ; 
 int MV88E6390_PORT_FLOW_CTL_UPDATE ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

int mv88e6390_port_pause_limit(struct mv88e6xxx_chip *chip, int port, u8 in,
			       u8 out)
{
	int err;

	err = mv88e6xxx_port_write(chip, port, MV88E6390_PORT_FLOW_CTL,
				   MV88E6390_PORT_FLOW_CTL_UPDATE |
				   MV88E6390_PORT_FLOW_CTL_LIMIT_IN | in);
	if (err)
		return err;

	return mv88e6xxx_port_write(chip, port, MV88E6390_PORT_FLOW_CTL,
				    MV88E6390_PORT_FLOW_CTL_UPDATE |
				    MV88E6390_PORT_FLOW_CTL_LIMIT_OUT | out);
}