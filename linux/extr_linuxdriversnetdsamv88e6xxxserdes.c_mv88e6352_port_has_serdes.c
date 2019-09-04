#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct mv88e6xxx_chip {TYPE_1__* ports; } ;
struct TYPE_2__ {scalar_t__ cmode; } ;

/* Variables and functions */
 scalar_t__ MV88E6XXX_PORT_STS_CMODE_1000BASE_X ; 
 scalar_t__ MV88E6XXX_PORT_STS_CMODE_100BASE_X ; 
 scalar_t__ MV88E6XXX_PORT_STS_CMODE_SGMII ; 

__attribute__((used)) static bool mv88e6352_port_has_serdes(struct mv88e6xxx_chip *chip, int port)
{
	u8 cmode = chip->ports[port].cmode;

	if ((cmode == MV88E6XXX_PORT_STS_CMODE_100BASE_X) ||
	    (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASE_X) ||
	    (cmode == MV88E6XXX_PORT_STS_CMODE_SGMII))
		return true;

	return false;
}