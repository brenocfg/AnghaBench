#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ autoneg; scalar_t__ link; } ;
struct TYPE_4__ {scalar_t__ (* link_status ) (struct xgbe_prv_data*,int*) ;} ;
struct TYPE_5__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; int /*<<< orphan*/  dev_state; TYPE_3__ phy; TYPE_2__ phy_if; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  XGBE_LINK_ERR ; 
 int /*<<< orphan*/  XGBE_LINK_INIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct xgbe_prv_data*,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_check_link_timeout (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_adjust_link (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_aneg_done (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_config_aneg (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_status_result (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_status(struct xgbe_prv_data *pdata)
{
	unsigned int link_aneg;
	int an_restart;

	if (test_bit(XGBE_LINK_ERR, &pdata->dev_state)) {
		netif_carrier_off(pdata->netdev);

		pdata->phy.link = 0;
		goto adjust_link;
	}

	link_aneg = (pdata->phy.autoneg == AUTONEG_ENABLE);

	pdata->phy.link = pdata->phy_if.phy_impl.link_status(pdata,
							     &an_restart);
	if (an_restart) {
		xgbe_phy_config_aneg(pdata);
		return;
	}

	if (pdata->phy.link) {
		if (link_aneg && !xgbe_phy_aneg_done(pdata)) {
			xgbe_check_link_timeout(pdata);
			return;
		}

		xgbe_phy_status_result(pdata);

		if (test_bit(XGBE_LINK_INIT, &pdata->dev_state))
			clear_bit(XGBE_LINK_INIT, &pdata->dev_state);

		netif_carrier_on(pdata->netdev);
	} else {
		if (test_bit(XGBE_LINK_INIT, &pdata->dev_state)) {
			xgbe_check_link_timeout(pdata);

			if (link_aneg)
				return;
		}

		xgbe_phy_status_result(pdata);

		netif_carrier_off(pdata->netdev);
	}

adjust_link:
	xgbe_phy_adjust_link(pdata);
}