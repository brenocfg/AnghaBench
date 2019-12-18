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
typedef  int u16 ;
struct phy_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  mdix_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TP_MDI_AUTO ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED_2 ; 
 int /*<<< orphan*/  MSCC_PHY_RGMII_CNTL ; 
 int RGMII_RX_CLK_DELAY_1_1_NS ; 
 int /*<<< orphan*/  RGMII_RX_CLK_DELAY_MASK ; 
 int RGMII_RX_CLK_DELAY_POS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_modify_paged (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vsc85xx_default_config(struct phy_device *phydev)
{
	int rc;
	u16 reg_val;

	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;
	mutex_lock(&phydev->lock);

	reg_val = RGMII_RX_CLK_DELAY_1_1_NS << RGMII_RX_CLK_DELAY_POS;

	rc = phy_modify_paged(phydev, MSCC_PHY_PAGE_EXTENDED_2,
			      MSCC_PHY_RGMII_CNTL, RGMII_RX_CLK_DELAY_MASK,
			      reg_val);

	mutex_unlock(&phydev->lock);

	return rc;
}