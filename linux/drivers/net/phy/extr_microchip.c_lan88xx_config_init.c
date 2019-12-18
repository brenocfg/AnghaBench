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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  PHY_ARDENNES_MMD_DEV_3_PHY_CFG ; 
 int PHY_ARDENNES_MMD_DEV_3_PHY_CFG_ZD_DLY_EN_ ; 
 int /*<<< orphan*/  lan88xx_config_TR_regs (struct phy_device*) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan88xx_config_init(struct phy_device *phydev)
{
	int val;

	/*Zerodetect delay enable */
	val = phy_read_mmd(phydev, MDIO_MMD_PCS,
			   PHY_ARDENNES_MMD_DEV_3_PHY_CFG);
	val |= PHY_ARDENNES_MMD_DEV_3_PHY_CFG_ZD_DLY_EN_;

	phy_write_mmd(phydev, MDIO_MMD_PCS, PHY_ARDENNES_MMD_DEV_3_PHY_CFG,
		      val);

	/* Config DSP registers */
	lan88xx_config_TR_regs(phydev);

	return 0;
}