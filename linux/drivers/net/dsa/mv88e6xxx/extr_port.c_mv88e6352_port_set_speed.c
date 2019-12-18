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

int mv88e6352_port_set_speed(struct mv88e6xxx_chip *chip, int port, int speed)
{
	if (speed == SPEED_MAX)
		speed = 1000;

	if (speed > 1000)
		return -EOPNOTSUPP;

	if (speed == 200 && port < 5)
		return -EOPNOTSUPP;

	return mv88e6xxx_port_set_speed(chip, port, speed, true, false);
}