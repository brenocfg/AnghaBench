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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int /*<<< orphan*/  cur_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGBE_MODE_KR ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xgbe_phy_perform_ratechange (struct xgbe_prv_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_phy_set_redrv_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_kr_mode(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_set_redrv_mode(pdata);

	/* 10G/KR */
	xgbe_phy_perform_ratechange(pdata, 4, 0);

	phy_data->cur_mode = XGBE_MODE_KR;

	netif_dbg(pdata, link, pdata->netdev, "10GbE KR mode set\n");
}