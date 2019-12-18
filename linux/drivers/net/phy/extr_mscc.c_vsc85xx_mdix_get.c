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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TP_MDI ; 
 int /*<<< orphan*/  ETH_TP_MDI_X ; 
 int HP_AUTO_MDIX_X_OVER_IND_MASK ; 
 int /*<<< orphan*/  MSCC_PHY_DEV_AUX_CNTL ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc85xx_mdix_get(struct phy_device *phydev, u8 *mdix)
{
	u16 reg_val;

	reg_val = phy_read(phydev, MSCC_PHY_DEV_AUX_CNTL);
	if (reg_val & HP_AUTO_MDIX_X_OVER_IND_MASK)
		*mdix = ETH_TP_MDI_X;
	else
		*mdix = ETH_TP_MDI;

	return 0;
}