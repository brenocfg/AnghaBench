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
 int EOPNOTSUPP ; 
 int SPEED_MAX ; 
 int mv88e6xxx_port_set_speed (struct mv88e6xxx_chip*,int,int,int,int) ; 

int mv88e6065_port_set_speed(struct mv88e6xxx_chip *chip, int port, int speed)
{
	if (speed == SPEED_MAX)
		speed = 200;

	if (speed > 200)
		return -EOPNOTSUPP;

	/* Setting 200 Mbps on port 0 to 3 selects 100 Mbps */
	return mv88e6xxx_port_set_speed(chip, port, speed, false, false);
}