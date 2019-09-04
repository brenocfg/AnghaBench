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
struct TYPE_3__ {int /*<<< orphan*/  tc_cnt; } ;
struct xgbe_prv_data {TYPE_2__* pfc; TYPE_1__ hw_feat; } ;
struct net_device {int dummy; } ;
struct ieee_pfc {int /*<<< orphan*/  delay; int /*<<< orphan*/  mbc; int /*<<< orphan*/  pfc_en; int /*<<< orphan*/  pfc_cap; } ;
struct TYPE_4__ {int /*<<< orphan*/  delay; int /*<<< orphan*/  mbc; int /*<<< orphan*/  pfc_en; } ;

/* Variables and functions */
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int xgbe_dcb_ieee_getpfc(struct net_device *netdev,
				struct ieee_pfc *pfc)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);

	/* Set number of supported PFC traffic classes */
	pfc->pfc_cap = pdata->hw_feat.tc_cnt;

	if (pdata->pfc) {
		pfc->pfc_en = pdata->pfc->pfc_en;
		pfc->mbc = pdata->pfc->mbc;
		pfc->delay = pdata->pfc->delay;
	}

	return 0;
}