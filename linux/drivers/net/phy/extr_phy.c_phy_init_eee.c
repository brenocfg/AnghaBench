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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {scalar_t__ duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EIO ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_AN_EEE_LPABLE ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_PCS_CTRL1_CLKSTOP_EN ; 
 int /*<<< orphan*/  MDIO_PCS_EEE_ABLE ; 
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv ; 
 int /*<<< orphan*/  common ; 
 int /*<<< orphan*/  linkmode_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lp ; 
 int /*<<< orphan*/  mmd_eee_adv_to_linkmode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmd_eee_cap_to_ethtool_sup_t (int) ; 
 int /*<<< orphan*/  phy_check_valid (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_read_status (struct phy_device*) ; 
 int /*<<< orphan*/  phy_set_bits_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int phy_init_eee(struct phy_device *phydev, bool clk_stop_enable)
{
	if (!phydev->drv)
		return -EIO;

	/* According to 802.3az,the EEE is supported only in full duplex-mode.
	 */
	if (phydev->duplex == DUPLEX_FULL) {
		__ETHTOOL_DECLARE_LINK_MODE_MASK(common);
		__ETHTOOL_DECLARE_LINK_MODE_MASK(lp);
		__ETHTOOL_DECLARE_LINK_MODE_MASK(adv);
		int eee_lp, eee_cap, eee_adv;
		int status;
		u32 cap;

		/* Read phy status to properly get the right settings */
		status = phy_read_status(phydev);
		if (status)
			return status;

		/* First check if the EEE ability is supported */
		eee_cap = phy_read_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_EEE_ABLE);
		if (eee_cap <= 0)
			goto eee_exit_err;

		cap = mmd_eee_cap_to_ethtool_sup_t(eee_cap);
		if (!cap)
			goto eee_exit_err;

		/* Check which link settings negotiated and verify it in
		 * the EEE advertising registers.
		 */
		eee_lp = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_LPABLE);
		if (eee_lp <= 0)
			goto eee_exit_err;

		eee_adv = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV);
		if (eee_adv <= 0)
			goto eee_exit_err;

		mmd_eee_adv_to_linkmode(adv, eee_adv);
		mmd_eee_adv_to_linkmode(lp, eee_lp);
		linkmode_and(common, adv, lp);

		if (!phy_check_valid(phydev->speed, phydev->duplex, common))
			goto eee_exit_err;

		if (clk_stop_enable)
			/* Configure the PHY to stop receiving xMII
			 * clock while it is signaling LPI.
			 */
			phy_set_bits_mmd(phydev, MDIO_MMD_PCS, MDIO_CTRL1,
					 MDIO_PCS_CTRL1_CLKSTOP_EN);

		return 0; /* EEE supported */
	}
eee_exit_err:
	return -EPROTONOSUPPORT;
}