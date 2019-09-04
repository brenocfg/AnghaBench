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
struct TYPE_3__ {int /*<<< orphan*/  (* an_post ) (struct xgbe_prv_data*) ;} ;
struct TYPE_4__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {int an_state; int an_int; scalar_t__ an_mode; int an_status; int an_result; int /*<<< orphan*/  netdev; TYPE_2__ phy_if; } ;
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
 int XGBE_AN_CL37_INT_CMPLT ; 
#define  XGBE_AN_COMPLETE 130 
 int XGBE_AN_ERROR ; 
 scalar_t__ XGBE_AN_MODE_CL37_SGMII ; 
#define  XGBE_AN_NO_LINK 129 
#define  XGBE_AN_READY 128 
 int XGBE_SGMII_AN_LINK_STATUS ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an37_clear_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an37_enable_interrupts (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_state_as_string (int) ; 

__attribute__((used)) static void xgbe_an37_state_machine(struct xgbe_prv_data *pdata)
{
	enum xgbe_an cur_state = pdata->an_state;

	if (!pdata->an_int)
		return;

	if (pdata->an_int & XGBE_AN_CL37_INT_CMPLT) {
		pdata->an_state = XGBE_AN_COMPLETE;
		pdata->an_int &= ~XGBE_AN_CL37_INT_CMPLT;

		/* If SGMII is enabled, check the link status */
		if ((pdata->an_mode == XGBE_AN_MODE_CL37_SGMII) &&
		    !(pdata->an_status & XGBE_SGMII_AN_LINK_STATUS))
			pdata->an_state = XGBE_AN_NO_LINK;
	}

	netif_dbg(pdata, link, pdata->netdev, "CL37 AN %s\n",
		  xgbe_state_as_string(pdata->an_state));

	cur_state = pdata->an_state;

	switch (pdata->an_state) {
	case XGBE_AN_READY:
		break;

	case XGBE_AN_COMPLETE:
		netif_dbg(pdata, link, pdata->netdev,
			  "Auto negotiation successful\n");
		break;

	case XGBE_AN_NO_LINK:
		break;

	default:
		pdata->an_state = XGBE_AN_ERROR;
	}

	if (pdata->an_state == XGBE_AN_ERROR) {
		netdev_err(pdata->netdev,
			   "error during auto-negotiation, state=%u\n",
			   cur_state);

		pdata->an_int = 0;
		xgbe_an37_clear_interrupts(pdata);
	}

	if (pdata->an_state >= XGBE_AN_COMPLETE) {
		pdata->an_result = pdata->an_state;
		pdata->an_state = XGBE_AN_READY;

		if (pdata->phy_if.phy_impl.an_post)
			pdata->phy_if.phy_impl.an_post(pdata);

		netif_dbg(pdata, link, pdata->netdev, "CL37 AN result: %s\n",
			  xgbe_state_as_string(pdata->an_result));
	}

	xgbe_an37_enable_interrupts(pdata);
}