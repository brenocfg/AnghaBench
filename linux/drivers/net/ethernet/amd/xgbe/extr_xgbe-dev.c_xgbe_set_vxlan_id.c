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
struct xgbe_prv_data {int /*<<< orphan*/  vxlan_port; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_TIR ; 
 int /*<<< orphan*/  TNID ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_set_vxlan_id(struct xgbe_prv_data *pdata)
{
	/* Program the VXLAN port */
	XGMAC_IOWRITE_BITS(pdata, MAC_TIR, TNID, pdata->vxlan_port);

	netif_dbg(pdata, drv, pdata->netdev, "VXLAN tunnel id set to %hx\n",
		  pdata->vxlan_port);
}