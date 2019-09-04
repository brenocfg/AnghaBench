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
struct TYPE_3__ {int /*<<< orphan*/  rss; } ;
struct xgbe_prv_data {TYPE_2__* netdev; TYPE_1__ hw_feat; } ;
struct TYPE_4__ {int features; } ;

/* Variables and functions */
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int xgbe_disable_rss (struct xgbe_prv_data*) ; 
 int xgbe_enable_rss (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_config_rss(struct xgbe_prv_data *pdata)
{
	int ret;

	if (!pdata->hw_feat.rss)
		return;

	if (pdata->netdev->features & NETIF_F_RXHASH)
		ret = xgbe_enable_rss(pdata);
	else
		ret = xgbe_disable_rss(pdata);

	if (ret)
		netdev_err(pdata->netdev,
			   "error configuring RSS, RSS disabled\n");
}