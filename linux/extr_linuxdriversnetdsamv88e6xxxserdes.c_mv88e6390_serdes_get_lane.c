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
 int ENODEV ; 
 int MV88E6390_PORT10_LANE0 ; 
 int MV88E6390_PORT9_LANE0 ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_1000BASE_X ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_2500BASEX ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_SGMII ; 

__attribute__((used)) static int mv88e6390_serdes_get_lane(struct mv88e6xxx_chip *chip, int port)
{
	u8 cmode = chip->ports[port].cmode;

	switch (port) {
	case 9:
		if (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			return MV88E6390_PORT9_LANE0;
		return -ENODEV;
	case 10:
		if (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			return MV88E6390_PORT10_LANE0;
		return -ENODEV;
	default:
		return -ENODEV;
	}
}