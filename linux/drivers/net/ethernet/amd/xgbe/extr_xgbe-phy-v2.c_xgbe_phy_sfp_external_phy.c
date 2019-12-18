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
struct xgbe_prv_data {struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int sfp_phy_avail; scalar_t__ sfp_base; int /*<<< orphan*/  sfp_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ XGBE_SFP_BASE_1000_T ; 
 int xgbe_phy_i2c_mii_read (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_phy_sfp_external_phy(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	int ret;

	if (!phy_data->sfp_changed)
		return;

	phy_data->sfp_phy_avail = 0;

	if (phy_data->sfp_base != XGBE_SFP_BASE_1000_T)
		return;

	/* Check access to the PHY by reading CTRL1 */
	ret = xgbe_phy_i2c_mii_read(pdata, MII_BMCR);
	if (ret < 0)
		return;

	/* Successfully accessed the PHY */
	phy_data->sfp_phy_avail = 1;
}