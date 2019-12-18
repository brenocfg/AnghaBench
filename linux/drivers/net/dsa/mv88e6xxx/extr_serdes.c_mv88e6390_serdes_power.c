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
typedef  int u8 ;
struct mv88e6xxx_chip {TYPE_1__* ports; } ;
struct TYPE_2__ {int cmode; } ;

/* Variables and functions */
#define  MV88E6XXX_PORT_STS_CMODE_1000BASEX 132 
#define  MV88E6XXX_PORT_STS_CMODE_2500BASEX 131 
#define  MV88E6XXX_PORT_STS_CMODE_RXAUI 130 
#define  MV88E6XXX_PORT_STS_CMODE_SGMII 129 
#define  MV88E6XXX_PORT_STS_CMODE_XAUI 128 
 int mv88e6390_serdes_power_10g (struct mv88e6xxx_chip*,int,int) ; 
 int mv88e6390_serdes_power_sgmii (struct mv88e6xxx_chip*,int,int) ; 

int mv88e6390_serdes_power(struct mv88e6xxx_chip *chip, int port, u8 lane,
			   bool up)
{
	u8 cmode = chip->ports[port].cmode;

	switch (cmode) {
	case MV88E6XXX_PORT_STS_CMODE_SGMII:
	case MV88E6XXX_PORT_STS_CMODE_1000BASEX:
	case MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		return mv88e6390_serdes_power_sgmii(chip, lane, up);
	case MV88E6XXX_PORT_STS_CMODE_XAUI:
	case MV88E6XXX_PORT_STS_CMODE_RXAUI:
		return mv88e6390_serdes_power_10g(chip, lane, up);
	}

	return 0;
}