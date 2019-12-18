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
typedef  int u32 ;
typedef  int u16 ;
struct alx_hw {int dummy; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_Pause ; 
 int ADVERTISE_CSMA ; 
 int /*<<< orphan*/  ALX_DRV ; 
 int /*<<< orphan*/  ALX_DRV_PHY ; 
 int ALX_FC_ANEG ; 
 int ALX_FC_RX ; 
 int ALX_FC_TX ; 
 int /*<<< orphan*/  ALX_MII_DBG_ADDR ; 
 int ALX_PHY_INITED ; 
 int /*<<< orphan*/  ALX_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_RESET ; 
 int BMCR_SPEED100 ; 
 int EBUSY ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 scalar_t__ alx_hw_giga (struct alx_hw*) ; 
 int alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int alx_write_phy_reg (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int ethadv_to_hw_cfg (struct alx_hw*,int) ; 
 int ethtool_adv_to_mii_adv_t (int) ; 
 int ethtool_adv_to_mii_ctrl1000_t (int) ; 

int alx_setup_speed_duplex(struct alx_hw *hw, u32 ethadv, u8 flowctrl)
{
	u16 adv, giga, cr;
	u32 val;
	int err = 0;

	alx_write_phy_reg(hw, ALX_MII_DBG_ADDR, 0);
	val = alx_read_mem32(hw, ALX_DRV);
	ALX_SET_FIELD(val, ALX_DRV_PHY, 0);

	if (ethadv & ADVERTISED_Autoneg) {
		adv = ADVERTISE_CSMA;
		adv |= ethtool_adv_to_mii_adv_t(ethadv);

		if (flowctrl & ALX_FC_ANEG) {
			if (flowctrl & ALX_FC_RX) {
				adv |= ADVERTISED_Pause;
				if (!(flowctrl & ALX_FC_TX))
					adv |= ADVERTISED_Asym_Pause;
			} else if (flowctrl & ALX_FC_TX) {
				adv |= ADVERTISED_Asym_Pause;
			}
		}
		giga = 0;
		if (alx_hw_giga(hw))
			giga = ethtool_adv_to_mii_ctrl1000_t(ethadv);

		cr = BMCR_RESET | BMCR_ANENABLE | BMCR_ANRESTART;

		if (alx_write_phy_reg(hw, MII_ADVERTISE, adv) ||
		    alx_write_phy_reg(hw, MII_CTRL1000, giga) ||
		    alx_write_phy_reg(hw, MII_BMCR, cr))
			err = -EBUSY;
	} else {
		cr = BMCR_RESET;
		if (ethadv == ADVERTISED_100baseT_Half ||
		    ethadv == ADVERTISED_100baseT_Full)
			cr |= BMCR_SPEED100;
		if (ethadv == ADVERTISED_10baseT_Full ||
		    ethadv == ADVERTISED_100baseT_Full)
			cr |= BMCR_FULLDPLX;

		err = alx_write_phy_reg(hw, MII_BMCR, cr);
	}

	if (!err) {
		alx_write_phy_reg(hw, ALX_MII_DBG_ADDR, ALX_PHY_INITED);
		val |= ethadv_to_hw_cfg(hw, ethadv);
	}

	alx_write_mem32(hw, ALX_DRV, val);

	return err;
}