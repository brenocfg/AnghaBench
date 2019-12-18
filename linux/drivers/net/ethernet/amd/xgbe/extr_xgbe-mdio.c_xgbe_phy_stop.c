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
struct TYPE_6__ {scalar_t__ link; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (struct xgbe_prv_data*) ;} ;
struct TYPE_5__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {scalar_t__ dev_irq; scalar_t__ an_irq; int /*<<< orphan*/  netdev; TYPE_3__ phy; TYPE_2__ phy_if; int /*<<< orphan*/  dev; scalar_t__ phy_started; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,scalar_t__,struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_disable_all (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_adjust_link (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_stop(struct xgbe_prv_data *pdata)
{
	netif_dbg(pdata, link, pdata->netdev, "stopping PHY\n");

	if (!pdata->phy_started)
		return;

	/* Indicate the PHY is down */
	pdata->phy_started = 0;

	/* Disable auto-negotiation */
	xgbe_an_disable_all(pdata);

	if (pdata->dev_irq != pdata->an_irq)
		devm_free_irq(pdata->dev, pdata->an_irq, pdata);

	pdata->phy_if.phy_impl.stop(pdata);

	pdata->phy.link = 0;
	netif_carrier_off(pdata->netdev);

	xgbe_phy_adjust_link(pdata);
}