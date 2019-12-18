#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vxn; } ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PFR ; 
 int /*<<< orphan*/  MAC_TCR ; 
 int /*<<< orphan*/  MAC_TIR ; 
 int /*<<< orphan*/  TNID ; 
 int /*<<< orphan*/  VNE ; 
 int /*<<< orphan*/  VUCC ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void xgbe_disable_vxlan(struct xgbe_prv_data *pdata)
{
	if (!pdata->hw_feat.vxn)
		return;

	/* Disable tunneling mode */
	XGMAC_IOWRITE_BITS(pdata, MAC_TCR, VNE, 0);

	/* Clear IPv6/UDP zero-checksum VXLAN packets setting */
	XGMAC_IOWRITE_BITS(pdata, MAC_PFR, VUCC, 0);

	/* Clear the VXLAN port */
	XGMAC_IOWRITE_BITS(pdata, MAC_TIR, TNID, 0);

	netif_dbg(pdata, drv, pdata->netdev, "VXLAN acceleration disabled\n");
}