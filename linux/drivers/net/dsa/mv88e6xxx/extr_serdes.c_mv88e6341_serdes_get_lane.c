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
typedef  int /*<<< orphan*/  u8 ;
struct mv88e6xxx_chip {TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6341_PORT5_LANE ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_1000BASEX ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_2500BASEX ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_SGMII ; 

u8 mv88e6341_serdes_get_lane(struct mv88e6xxx_chip *chip, int port)
{
	u8 cmode = chip->ports[port].cmode;
	u8 lane = 0;

	switch (port) {
	case 5:
		if (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			lane = MV88E6341_PORT5_LANE;
		break;
	}

	return lane;
}