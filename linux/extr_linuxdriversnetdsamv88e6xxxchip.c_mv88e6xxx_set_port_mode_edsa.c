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
 int /*<<< orphan*/  ETH_P_EDSA ; 
 int /*<<< orphan*/  MV88E6XXX_EGRESS_MODE_ETHERTYPE ; 
 int /*<<< orphan*/  MV88E6XXX_FRAME_MODE_ETHERTYPE ; 
 int mv88e6xxx_set_port_mode (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e6xxx_set_port_mode_edsa(struct mv88e6xxx_chip *chip, int port)
{
	return mv88e6xxx_set_port_mode(chip, port,
				       MV88E6XXX_FRAME_MODE_ETHERTYPE,
				       MV88E6XXX_EGRESS_MODE_ETHERTYPE,
				       ETH_P_EDSA);
}