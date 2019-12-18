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
typedef  size_t u8 ;
typedef  int u16 ;
struct ksz_device {TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  fiber; } ;

/* Variables and functions */
 int PHY_AUTO_MDIX_DISABLE ; 
 int PHY_AUTO_NEG_100BTX ; 
 int PHY_AUTO_NEG_100BTX_FD ; 
 int PHY_AUTO_NEG_10BT ; 
 int PHY_AUTO_NEG_10BT_FD ; 
 int PHY_AUTO_NEG_ENABLE ; 
 int PHY_AUTO_NEG_RESTART ; 
 int PHY_AUTO_NEG_SYM_PAUSE ; 
 int PHY_FORCE_MDIX ; 
 int PHY_FULL_DUPLEX ; 
 int PHY_HP_MDIX ; 
 int PHY_LED_DISABLE ; 
 int PHY_LOOPBACK ; 
 int PHY_POWER_DOWN ; 
#define  PHY_REG_AUTO_NEGOTIATION 129 
#define  PHY_REG_CTRL 128 
 int PHY_RESET ; 
 int PHY_SPEED_100MBIT ; 
 int PHY_TRANSMIT_DISABLE ; 
 size_t PORT_AUTO_MDIX_DISABLE ; 
 size_t PORT_AUTO_NEG_100BTX ; 
 size_t PORT_AUTO_NEG_100BTX_FD ; 
 size_t PORT_AUTO_NEG_10BT ; 
 size_t PORT_AUTO_NEG_10BT_FD ; 
 size_t PORT_AUTO_NEG_DISABLE ; 
 size_t PORT_AUTO_NEG_RESTART ; 
 size_t PORT_AUTO_NEG_SYM_PAUSE ; 
 size_t PORT_FORCE_100_MBIT ; 
 size_t PORT_FORCE_FULL_DUPLEX ; 
 size_t PORT_FORCE_MDIX ; 
 size_t PORT_HP_MDIX ; 
 size_t PORT_LED_OFF ; 
 size_t PORT_PHY_LOOPBACK ; 
 size_t PORT_POWER_DOWN ; 
 size_t PORT_TX_DISABLE ; 
 int /*<<< orphan*/  P_FORCE_CTRL ; 
 int /*<<< orphan*/  P_LOCAL_CTRL ; 
 int /*<<< orphan*/  P_NEG_RESTART_CTRL ; 
 int /*<<< orphan*/  P_SPEED_STATUS ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  ksz_pwrite8 (struct ksz_device*,size_t,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void ksz8795_w_phy(struct ksz_device *dev, u16 phy, u16 reg, u16 val)
{
	u8 p = phy;
	u8 restart, speed, ctrl, data;

	switch (reg) {
	case PHY_REG_CTRL:

		/* Do not support PHY reset function. */
		if (val & PHY_RESET)
			break;
		ksz_pread8(dev, p, P_SPEED_STATUS, &speed);
		data = speed;
		if (val & PHY_HP_MDIX)
			data |= PORT_HP_MDIX;
		else
			data &= ~PORT_HP_MDIX;
		if (data != speed)
			ksz_pwrite8(dev, p, P_SPEED_STATUS, data);
		ksz_pread8(dev, p, P_FORCE_CTRL, &ctrl);
		data = ctrl;
		if (!(val & PHY_AUTO_NEG_ENABLE))
			data |= PORT_AUTO_NEG_DISABLE;
		else
			data &= ~PORT_AUTO_NEG_DISABLE;

		/* Fiber port does not support auto-negotiation. */
		if (dev->ports[p].fiber)
			data |= PORT_AUTO_NEG_DISABLE;
		if (val & PHY_SPEED_100MBIT)
			data |= PORT_FORCE_100_MBIT;
		else
			data &= ~PORT_FORCE_100_MBIT;
		if (val & PHY_FULL_DUPLEX)
			data |= PORT_FORCE_FULL_DUPLEX;
		else
			data &= ~PORT_FORCE_FULL_DUPLEX;
		if (data != ctrl)
			ksz_pwrite8(dev, p, P_FORCE_CTRL, data);
		ksz_pread8(dev, p, P_NEG_RESTART_CTRL, &restart);
		data = restart;
		if (val & PHY_LED_DISABLE)
			data |= PORT_LED_OFF;
		else
			data &= ~PORT_LED_OFF;
		if (val & PHY_TRANSMIT_DISABLE)
			data |= PORT_TX_DISABLE;
		else
			data &= ~PORT_TX_DISABLE;
		if (val & PHY_AUTO_NEG_RESTART)
			data |= PORT_AUTO_NEG_RESTART;
		else
			data &= ~(PORT_AUTO_NEG_RESTART);
		if (val & PHY_POWER_DOWN)
			data |= PORT_POWER_DOWN;
		else
			data &= ~PORT_POWER_DOWN;
		if (val & PHY_AUTO_MDIX_DISABLE)
			data |= PORT_AUTO_MDIX_DISABLE;
		else
			data &= ~PORT_AUTO_MDIX_DISABLE;
		if (val & PHY_FORCE_MDIX)
			data |= PORT_FORCE_MDIX;
		else
			data &= ~PORT_FORCE_MDIX;
		if (val & PHY_LOOPBACK)
			data |= PORT_PHY_LOOPBACK;
		else
			data &= ~PORT_PHY_LOOPBACK;
		if (data != restart)
			ksz_pwrite8(dev, p, P_NEG_RESTART_CTRL, data);
		break;
	case PHY_REG_AUTO_NEGOTIATION:
		ksz_pread8(dev, p, P_LOCAL_CTRL, &ctrl);
		data = ctrl;
		data &= ~(PORT_AUTO_NEG_SYM_PAUSE |
			  PORT_AUTO_NEG_100BTX_FD |
			  PORT_AUTO_NEG_100BTX |
			  PORT_AUTO_NEG_10BT_FD |
			  PORT_AUTO_NEG_10BT);
		if (val & PHY_AUTO_NEG_SYM_PAUSE)
			data |= PORT_AUTO_NEG_SYM_PAUSE;
		if (val & PHY_AUTO_NEG_100BTX_FD)
			data |= PORT_AUTO_NEG_100BTX_FD;
		if (val & PHY_AUTO_NEG_100BTX)
			data |= PORT_AUTO_NEG_100BTX;
		if (val & PHY_AUTO_NEG_10BT_FD)
			data |= PORT_AUTO_NEG_10BT_FD;
		if (val & PHY_AUTO_NEG_10BT)
			data |= PORT_AUTO_NEG_10BT;
		if (data != ctrl)
			ksz_pwrite8(dev, p, P_LOCAL_CTRL, data);
		break;
	default:
		break;
	}
}