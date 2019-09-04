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
struct TYPE_4__ {scalar_t__ hash_table_size; } ;
struct xgbe_prv_data {TYPE_2__ hw_feat; TYPE_1__* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMC ; 
 int /*<<< orphan*/  HPF ; 
 int /*<<< orphan*/  HUC ; 
 int /*<<< orphan*/  MAC_PFR ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgbe_set_mac_address (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_config_mac_address(struct xgbe_prv_data *pdata)
{
	xgbe_set_mac_address(pdata, pdata->netdev->dev_addr);

	/* Filtering is done using perfect filtering and hash filtering */
	if (pdata->hw_feat.hash_table_size) {
		XGMAC_IOWRITE_BITS(pdata, MAC_PFR, HPF, 1);
		XGMAC_IOWRITE_BITS(pdata, MAC_PFR, HUC, 1);
		XGMAC_IOWRITE_BITS(pdata, MAC_PFR, HMC, 1);
	}
}