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
 int /*<<< orphan*/  MV88E6095_PORT_IEEE_PRIO_REMAP_0123 ; 
 int /*<<< orphan*/  MV88E6095_PORT_IEEE_PRIO_REMAP_4567 ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int) ; 

int mv88e6095_port_tag_remap(struct mv88e6xxx_chip *chip, int port)
{
	int err;

	/* Use a direct priority mapping for all IEEE tagged frames */
	err = mv88e6xxx_port_write(chip, port,
				   MV88E6095_PORT_IEEE_PRIO_REMAP_0123,
				   0x3210);
	if (err)
		return err;

	return mv88e6xxx_port_write(chip, port,
				    MV88E6095_PORT_IEEE_PRIO_REMAP_4567,
				    0x7654);
}