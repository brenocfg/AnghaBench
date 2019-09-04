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
 int MV88E6390_PORT10_LANE1 ; 
 int MV88E6390_PORT10_LANE2 ; 
 int MV88E6390_PORT10_LANE3 ; 
 int MV88E6390_PORT9_LANE0 ; 
 int MV88E6390_PORT9_LANE1 ; 
 int MV88E6390_PORT9_LANE2 ; 
 int MV88E6390_PORT9_LANE3 ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_1000BASE_X ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_2500BASEX ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_RXAUI ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_SGMII ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_STS_CMODE_XAUI ; 

int mv88e6390x_serdes_get_lane(struct mv88e6xxx_chip *chip, int port)
{
	u8 cmode_port9, cmode_port10, cmode_port;

	cmode_port9 = chip->ports[9].cmode;
	cmode_port10 = chip->ports[10].cmode;
	cmode_port = chip->ports[port].cmode;

	switch (port) {
	case 2:
		if (cmode_port9 == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			if (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASE_X)
				return MV88E6390_PORT9_LANE1;
		return -ENODEV;
	case 3:
		if (cmode_port9 == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			if (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASE_X)
				return MV88E6390_PORT9_LANE2;
		return -ENODEV;
	case 4:
		if (cmode_port9 == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			if (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASE_X)
				return MV88E6390_PORT9_LANE3;
		return -ENODEV;
	case 5:
		if (cmode_port10 == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			if (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASE_X)
				return MV88E6390_PORT10_LANE1;
		return -ENODEV;
	case 6:
		if (cmode_port10 == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			if (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASE_X)
				return MV88E6390_PORT10_LANE2;
		return -ENODEV;
	case 7:
		if (cmode_port10 == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			if (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASE_X)
				return MV88E6390_PORT10_LANE3;
		return -ENODEV;
	case 9:
		if (cmode_port9 == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_XAUI ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			return MV88E6390_PORT9_LANE0;
		return -ENODEV;
	case 10:
		if (cmode_port10 == MV88E6XXX_PORT_STS_CMODE_1000BASE_X ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_XAUI ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			return MV88E6390_PORT10_LANE0;
		return -ENODEV;
	default:
		return -ENODEV;
	}
}