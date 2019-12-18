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
typedef  int u8 ;
typedef  int u16 ;
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int KSZ8795_ID_HI ; 
 int KSZ8795_ID_LO ; 
 int PHY_100BTX_CAPABLE ; 
 int PHY_100BTX_FD_CAPABLE ; 
 int PHY_10BT_CAPABLE ; 
 int PHY_10BT_FD_CAPABLE ; 
 int PHY_AUTO_MDIX_DISABLE ; 
 int PHY_AUTO_NEG_100BTX ; 
 int PHY_AUTO_NEG_100BTX_FD ; 
 int PHY_AUTO_NEG_10BT ; 
 int PHY_AUTO_NEG_10BT_FD ; 
 int PHY_AUTO_NEG_802_3 ; 
 int PHY_AUTO_NEG_ACKNOWLEDGE ; 
 int PHY_AUTO_NEG_CAPABLE ; 
 int PHY_AUTO_NEG_ENABLE ; 
 int PHY_AUTO_NEG_RESTART ; 
 int PHY_AUTO_NEG_SYM_PAUSE ; 
 int PHY_FORCE_MDIX ; 
 int PHY_FULL_DUPLEX ; 
 int PHY_HP_MDIX ; 
 int PHY_LED_DISABLE ; 
 int PHY_LINK_STATUS ; 
 int PHY_LOOPBACK ; 
 int PHY_POWER_DOWN ; 
#define  PHY_REG_AUTO_NEGOTIATION 133 
#define  PHY_REG_CTRL 132 
#define  PHY_REG_ID_1 131 
#define  PHY_REG_ID_2 130 
#define  PHY_REG_REMOTE_CAPABILITY 129 
#define  PHY_REG_STATUS 128 
 int PHY_REMOTE_ACKNOWLEDGE_NOT ; 
 int PHY_SPEED_100MBIT ; 
 int PHY_TRANSMIT_DISABLE ; 
 int PORT_AUTO_MDIX_DISABLE ; 
 int PORT_AUTO_NEG_100BTX ; 
 int PORT_AUTO_NEG_100BTX_FD ; 
 int PORT_AUTO_NEG_10BT ; 
 int PORT_AUTO_NEG_10BT_FD ; 
 int PORT_AUTO_NEG_COMPLETE ; 
 int PORT_AUTO_NEG_DISABLE ; 
 int PORT_AUTO_NEG_RESTART ; 
 int PORT_AUTO_NEG_SYM_PAUSE ; 
 int PORT_FORCE_100_MBIT ; 
 int PORT_FORCE_FULL_DUPLEX ; 
 int PORT_FORCE_MDIX ; 
 int PORT_HP_MDIX ; 
 int PORT_LED_OFF ; 
 int PORT_PHY_LOOPBACK ; 
 int PORT_POWER_DOWN ; 
 int PORT_REMOTE_100BTX ; 
 int PORT_REMOTE_100BTX_FD ; 
 int PORT_REMOTE_10BT ; 
 int PORT_REMOTE_10BT_FD ; 
 int PORT_REMOTE_SYM_PAUSE ; 
 int PORT_STAT_LINK_GOOD ; 
 int PORT_TX_DISABLE ; 
 int /*<<< orphan*/  P_FORCE_CTRL ; 
 int /*<<< orphan*/  P_LINK_STATUS ; 
 int /*<<< orphan*/  P_LOCAL_CTRL ; 
 int /*<<< orphan*/  P_NEG_RESTART_CTRL ; 
 int /*<<< orphan*/  P_REMOTE_STATUS ; 
 int /*<<< orphan*/  P_SPEED_STATUS ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void ksz8795_r_phy(struct ksz_device *dev, u16 phy, u16 reg, u16 *val)
{
	u8 restart, speed, ctrl, link;
	int processed = true;
	u16 data = 0;
	u8 p = phy;

	switch (reg) {
	case PHY_REG_CTRL:
		ksz_pread8(dev, p, P_NEG_RESTART_CTRL, &restart);
		ksz_pread8(dev, p, P_SPEED_STATUS, &speed);
		ksz_pread8(dev, p, P_FORCE_CTRL, &ctrl);
		if (restart & PORT_PHY_LOOPBACK)
			data |= PHY_LOOPBACK;
		if (ctrl & PORT_FORCE_100_MBIT)
			data |= PHY_SPEED_100MBIT;
		if (!(ctrl & PORT_AUTO_NEG_DISABLE))
			data |= PHY_AUTO_NEG_ENABLE;
		if (restart & PORT_POWER_DOWN)
			data |= PHY_POWER_DOWN;
		if (restart & PORT_AUTO_NEG_RESTART)
			data |= PHY_AUTO_NEG_RESTART;
		if (ctrl & PORT_FORCE_FULL_DUPLEX)
			data |= PHY_FULL_DUPLEX;
		if (speed & PORT_HP_MDIX)
			data |= PHY_HP_MDIX;
		if (restart & PORT_FORCE_MDIX)
			data |= PHY_FORCE_MDIX;
		if (restart & PORT_AUTO_MDIX_DISABLE)
			data |= PHY_AUTO_MDIX_DISABLE;
		if (restart & PORT_TX_DISABLE)
			data |= PHY_TRANSMIT_DISABLE;
		if (restart & PORT_LED_OFF)
			data |= PHY_LED_DISABLE;
		break;
	case PHY_REG_STATUS:
		ksz_pread8(dev, p, P_LINK_STATUS, &link);
		data = PHY_100BTX_FD_CAPABLE |
		       PHY_100BTX_CAPABLE |
		       PHY_10BT_FD_CAPABLE |
		       PHY_10BT_CAPABLE |
		       PHY_AUTO_NEG_CAPABLE;
		if (link & PORT_AUTO_NEG_COMPLETE)
			data |= PHY_AUTO_NEG_ACKNOWLEDGE;
		if (link & PORT_STAT_LINK_GOOD)
			data |= PHY_LINK_STATUS;
		break;
	case PHY_REG_ID_1:
		data = KSZ8795_ID_HI;
		break;
	case PHY_REG_ID_2:
		data = KSZ8795_ID_LO;
		break;
	case PHY_REG_AUTO_NEGOTIATION:
		ksz_pread8(dev, p, P_LOCAL_CTRL, &ctrl);
		data = PHY_AUTO_NEG_802_3;
		if (ctrl & PORT_AUTO_NEG_SYM_PAUSE)
			data |= PHY_AUTO_NEG_SYM_PAUSE;
		if (ctrl & PORT_AUTO_NEG_100BTX_FD)
			data |= PHY_AUTO_NEG_100BTX_FD;
		if (ctrl & PORT_AUTO_NEG_100BTX)
			data |= PHY_AUTO_NEG_100BTX;
		if (ctrl & PORT_AUTO_NEG_10BT_FD)
			data |= PHY_AUTO_NEG_10BT_FD;
		if (ctrl & PORT_AUTO_NEG_10BT)
			data |= PHY_AUTO_NEG_10BT;
		break;
	case PHY_REG_REMOTE_CAPABILITY:
		ksz_pread8(dev, p, P_REMOTE_STATUS, &link);
		data = PHY_AUTO_NEG_802_3;
		if (link & PORT_REMOTE_SYM_PAUSE)
			data |= PHY_AUTO_NEG_SYM_PAUSE;
		if (link & PORT_REMOTE_100BTX_FD)
			data |= PHY_AUTO_NEG_100BTX_FD;
		if (link & PORT_REMOTE_100BTX)
			data |= PHY_AUTO_NEG_100BTX;
		if (link & PORT_REMOTE_10BT_FD)
			data |= PHY_AUTO_NEG_10BT_FD;
		if (link & PORT_REMOTE_10BT)
			data |= PHY_AUTO_NEG_10BT;
		if (data & ~PHY_AUTO_NEG_802_3)
			data |= PHY_REMOTE_ACKNOWLEDGE_NOT;
		break;
	default:
		processed = false;
		break;
	}
	if (processed)
		*val = data;
}