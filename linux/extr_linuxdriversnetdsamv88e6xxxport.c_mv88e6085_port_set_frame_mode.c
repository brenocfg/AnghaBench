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
typedef  enum mv88e6xxx_frame_mode { ____Placeholder_mv88e6xxx_frame_mode } mv88e6xxx_frame_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  MV88E6XXX_FRAME_MODE_DSA 129 
#define  MV88E6XXX_FRAME_MODE_NORMAL 128 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL0 ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL0_FRAME_MODE_DSA ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL0_FRAME_MODE_MASK ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_CTL0_FRAME_MODE_NORMAL ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mv88e6xxx_port_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mv88e6085_port_set_frame_mode(struct mv88e6xxx_chip *chip, int port,
				  enum mv88e6xxx_frame_mode mode)
{
	int err;
	u16 reg;

	err = mv88e6xxx_port_read(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	if (err)
		return err;

	reg &= ~MV88E6XXX_PORT_CTL0_FRAME_MODE_MASK;

	switch (mode) {
	case MV88E6XXX_FRAME_MODE_NORMAL:
		reg |= MV88E6XXX_PORT_CTL0_FRAME_MODE_NORMAL;
		break;
	case MV88E6XXX_FRAME_MODE_DSA:
		reg |= MV88E6XXX_PORT_CTL0_FRAME_MODE_DSA;
		break;
	default:
		return -EINVAL;
	}

	return mv88e6xxx_port_write(chip, port, MV88E6XXX_PORT_CTL0, reg);
}