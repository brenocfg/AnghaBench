#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {int addr; int /*<<< orphan*/  bus; } ;
struct phy_device {TYPE_2__* drv; TYPE_1__ mdio; int /*<<< orphan*/  advertising; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; } ;
struct mii_ioctl_data {int val_in; int phy_id; int reg_num; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;
struct TYPE_4__ {int (* hwtstamp ) (struct phy_device*,struct ifreq*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_RESET ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int EOPNOTSUPP ; 
 int MII_ADDR_C45 ; 
#define  MII_ADVERTISE 134 
#define  MII_BMCR 133 
#define  MII_CTRL1000 132 
#define  SIOCGMIIPHY 131 
#define  SIOCGMIIREG 130 
#define  SIOCSHWTSTAMP 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int mdio_phy_id_devad (int) ; 
 int /*<<< orphan*/  mdio_phy_id_is_c45 (int) ; 
 int mdio_phy_id_prtad (int) ; 
 int /*<<< orphan*/  mdiobus_read (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mdiobus_write (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mii_adv_mod_linkmode_adv_t (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_ctrl1000_mod_linkmode_adv_t (int /*<<< orphan*/ ,int) ; 
 int phy_init_hw (struct phy_device*) ; 
 int phy_start_aneg (struct phy_device*) ; 
 int stub1 (struct phy_device*,struct ifreq*) ; 

int phy_mii_ioctl(struct phy_device *phydev, struct ifreq *ifr, int cmd)
{
	struct mii_ioctl_data *mii_data = if_mii(ifr);
	u16 val = mii_data->val_in;
	bool change_autoneg = false;
	int prtad, devad;

	switch (cmd) {
	case SIOCGMIIPHY:
		mii_data->phy_id = phydev->mdio.addr;
		/* fall through */

	case SIOCGMIIREG:
		if (mdio_phy_id_is_c45(mii_data->phy_id)) {
			prtad = mdio_phy_id_prtad(mii_data->phy_id);
			devad = mdio_phy_id_devad(mii_data->phy_id);
			devad = MII_ADDR_C45 | devad << 16 | mii_data->reg_num;
		} else {
			prtad = mii_data->phy_id;
			devad = mii_data->reg_num;
		}
		mii_data->val_out = mdiobus_read(phydev->mdio.bus, prtad,
						 devad);
		return 0;

	case SIOCSMIIREG:
		if (mdio_phy_id_is_c45(mii_data->phy_id)) {
			prtad = mdio_phy_id_prtad(mii_data->phy_id);
			devad = mdio_phy_id_devad(mii_data->phy_id);
			devad = MII_ADDR_C45 | devad << 16 | mii_data->reg_num;
		} else {
			prtad = mii_data->phy_id;
			devad = mii_data->reg_num;
		}
		if (prtad == phydev->mdio.addr) {
			switch (devad) {
			case MII_BMCR:
				if ((val & (BMCR_RESET | BMCR_ANENABLE)) == 0) {
					if (phydev->autoneg == AUTONEG_ENABLE)
						change_autoneg = true;
					phydev->autoneg = AUTONEG_DISABLE;
					if (val & BMCR_FULLDPLX)
						phydev->duplex = DUPLEX_FULL;
					else
						phydev->duplex = DUPLEX_HALF;
					if (val & BMCR_SPEED1000)
						phydev->speed = SPEED_1000;
					else if (val & BMCR_SPEED100)
						phydev->speed = SPEED_100;
					else phydev->speed = SPEED_10;
				}
				else {
					if (phydev->autoneg == AUTONEG_DISABLE)
						change_autoneg = true;
					phydev->autoneg = AUTONEG_ENABLE;
				}
				break;
			case MII_ADVERTISE:
				mii_adv_mod_linkmode_adv_t(phydev->advertising,
							   val);
				change_autoneg = true;
				break;
			case MII_CTRL1000:
				mii_ctrl1000_mod_linkmode_adv_t(phydev->advertising,
							        val);
				change_autoneg = true;
				break;
			default:
				/* do nothing */
				break;
			}
		}

		mdiobus_write(phydev->mdio.bus, prtad, devad, val);

		if (prtad == phydev->mdio.addr &&
		    devad == MII_BMCR &&
		    val & BMCR_RESET)
			return phy_init_hw(phydev);

		if (change_autoneg)
			return phy_start_aneg(phydev);

		return 0;

	case SIOCSHWTSTAMP:
		if (phydev->drv && phydev->drv->hwtstamp)
			return phydev->drv->hwtstamp(phydev, ifr);
		/* fall through */

	default:
		return -EOPNOTSUPP;
	}
}