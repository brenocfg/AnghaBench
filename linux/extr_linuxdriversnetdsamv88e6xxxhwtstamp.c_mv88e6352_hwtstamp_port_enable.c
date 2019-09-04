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
 int /*<<< orphan*/  MV88E6XXX_PORT_PTP_CFG0 ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_PTP_CFG0_DISABLE_TSPEC_MATCH ; 
 int mv88e6xxx_port_ptp_write (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mv88e6352_hwtstamp_port_enable(struct mv88e6xxx_chip *chip, int port)
{
	return mv88e6xxx_port_ptp_write(chip, port, MV88E6XXX_PORT_PTP_CFG0,
					MV88E6XXX_PORT_PTP_CFG0_DISABLE_TSPEC_MATCH);
}