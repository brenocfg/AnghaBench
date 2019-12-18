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
typedef  int u32 ;
struct mii_if_info {int /*<<< orphan*/  phy_id; } ;
struct usbnet {int /*<<< orphan*/  net; struct mii_if_info mii; scalar_t__* data; } ;
struct smsc95xx_priv {int features; int /*<<< orphan*/  suspend_flags; } ;

/* Variables and functions */
 int FEATURE_PHY_NLP_CROSSOVER ; 
 int MODE_CTRL_STS_EDPWRDOWN_ ; 
 int /*<<< orphan*/  PHY_EDPD_CONFIG ; 
 int PHY_EDPD_CONFIG_DEFAULT ; 
 int /*<<< orphan*/  PHY_MODE_CTRL_STS ; 
 int PM_CTL_ED_EN_ ; 
 int PM_CTL_PHY_RST_ ; 
 int PM_CTL_SUS_MODE_ ; 
 int PM_CTL_SUS_MODE_1 ; 
 int PM_CTL_WUPS_ ; 
 int PM_CTL_WUPS_ED_ ; 
 int /*<<< orphan*/  PM_CTRL ; 
 int /*<<< orphan*/  SUSPEND_SUSPEND1 ; 
 int smsc95xx_mdio_read_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc95xx_mdio_write_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int smsc95xx_read_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int smsc95xx_write_reg_nopm (struct usbnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc95xx_enter_suspend1(struct usbnet *dev)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);
	struct mii_if_info *mii = &dev->mii;
	u32 val;
	int ret;

	/* reconfigure link pulse detection timing for
	 * compatibility with non-standard link partners
	 */
	if (pdata->features & FEATURE_PHY_NLP_CROSSOVER)
		smsc95xx_mdio_write_nopm(dev->net, mii->phy_id,	PHY_EDPD_CONFIG,
			PHY_EDPD_CONFIG_DEFAULT);

	/* enable energy detect power-down mode */
	ret = smsc95xx_mdio_read_nopm(dev->net, mii->phy_id, PHY_MODE_CTRL_STS);
	if (ret < 0)
		return ret;

	ret |= MODE_CTRL_STS_EDPWRDOWN_;

	smsc95xx_mdio_write_nopm(dev->net, mii->phy_id, PHY_MODE_CTRL_STS, ret);

	/* enter SUSPEND1 mode */
	ret = smsc95xx_read_reg_nopm(dev, PM_CTRL, &val);
	if (ret < 0)
		return ret;

	val &= ~(PM_CTL_SUS_MODE_ | PM_CTL_WUPS_ | PM_CTL_PHY_RST_);
	val |= PM_CTL_SUS_MODE_1;

	ret = smsc95xx_write_reg_nopm(dev, PM_CTRL, val);
	if (ret < 0)
		return ret;

	/* clear wol status, enable energy detection */
	val &= ~PM_CTL_WUPS_;
	val |= (PM_CTL_WUPS_ED_ | PM_CTL_ED_EN_);

	ret = smsc95xx_write_reg_nopm(dev, PM_CTRL, val);
	if (ret < 0)
		return ret;

	pdata->suspend_flags |= SUSPEND_SUSPEND1;

	return 0;
}