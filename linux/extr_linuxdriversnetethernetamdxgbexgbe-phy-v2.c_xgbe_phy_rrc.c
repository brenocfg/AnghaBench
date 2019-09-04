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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xgbe_phy_perform_ratechange (struct xgbe_prv_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_phy_rrc(struct xgbe_prv_data *pdata)
{
	/* Receiver Reset Cycle */
	xgbe_phy_perform_ratechange(pdata, 5, 0);

	netif_dbg(pdata, link, pdata->netdev, "receiver reset complete\n");
}