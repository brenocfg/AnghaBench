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
typedef  int phy_interface_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  PHY_INTERFACE_MODE_NA 131 
#define  PHY_INTERFACE_MODE_RXAUI 130 
#define  PHY_INTERFACE_MODE_XAUI 129 
#define  PHY_INTERFACE_MODE_XGMII 128 
 int mv88e6341_port_set_cmode_writable (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_port_set_cmode (struct mv88e6xxx_chip*,int,int) ; 

int mv88e6341_port_set_cmode(struct mv88e6xxx_chip *chip, int port,
			     phy_interface_t mode)
{
	int err;

	if (port != 5)
		return -EOPNOTSUPP;

	switch (mode) {
	case PHY_INTERFACE_MODE_NA:
		return 0;
	case PHY_INTERFACE_MODE_XGMII:
	case PHY_INTERFACE_MODE_XAUI:
	case PHY_INTERFACE_MODE_RXAUI:
		return -EINVAL;
	default:
		break;
	}

	err = mv88e6341_port_set_cmode_writable(chip, port);
	if (err)
		return err;

	return mv88e6xxx_port_set_cmode(chip, port, mode);
}