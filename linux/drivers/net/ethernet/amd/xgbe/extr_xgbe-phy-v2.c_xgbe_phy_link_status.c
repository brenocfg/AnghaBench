#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ autoneg; } ;
struct xgbe_prv_data {TYPE_1__ phy; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ port_mode; scalar_t__ rrc_count; TYPE_2__* phydev; scalar_t__ sfp_rx_los; scalar_t__ sfp_mod_absent; scalar_t__ sfp_changed; } ;
struct TYPE_5__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 unsigned int MDIO_STAT1_LSTATUS ; 
 scalar_t__ XGBE_PORT_MODE_SFP ; 
 scalar_t__ XGBE_RRC_FREQUENCY ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_aneg_done (TYPE_2__*) ; 
 int phy_read_status (TYPE_2__*) ; 
 int /*<<< orphan*/  xgbe_phy_rrc (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_sfp_detect (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_link_status(struct xgbe_prv_data *pdata, int *an_restart)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	unsigned int reg;
	int ret;

	*an_restart = 0;

	if (phy_data->port_mode == XGBE_PORT_MODE_SFP) {
		/* Check SFP signals */
		xgbe_phy_sfp_detect(pdata);

		if (phy_data->sfp_changed) {
			*an_restart = 1;
			return 0;
		}

		if (phy_data->sfp_mod_absent || phy_data->sfp_rx_los)
			return 0;
	}

	if (phy_data->phydev) {
		/* Check external PHY */
		ret = phy_read_status(phy_data->phydev);
		if (ret < 0)
			return 0;

		if ((pdata->phy.autoneg == AUTONEG_ENABLE) &&
		    !phy_aneg_done(phy_data->phydev))
			return 0;

		if (!phy_data->phydev->link)
			return 0;
	}

	/* Link status is latched low, so read once to clear
	 * and then read again to get current state
	 */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	if (reg & MDIO_STAT1_LSTATUS)
		return 1;

	/* No link, attempt a receiver reset cycle */
	if (phy_data->rrc_count++ > XGBE_RRC_FREQUENCY) {
		phy_data->rrc_count = 0;
		xgbe_phy_rrc(pdata);
	}

	return 0;
}