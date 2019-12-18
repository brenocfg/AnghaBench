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
struct TYPE_2__ {int mmds; } ;
struct ef4_nic {scalar_t__ loopback_mode; TYPE_1__ mdio; } ;

/* Variables and functions */
 scalar_t__ LOOPBACK_INTERNAL (struct ef4_nic*) ; 
 scalar_t__ LOOPBACK_XGMII ; 
 int MDIO_MMD_PHYXS ; 
 scalar_t__ ef4_mdio_phyxgxs_lane_sync (struct ef4_nic*) ; 
 scalar_t__ falcon_xgxs_link_ok (struct ef4_nic*) ; 

__attribute__((used)) static bool falcon_xmac_link_ok(struct ef4_nic *efx)
{
	/*
	 * Check MAC's XGXS link status except when using XGMII loopback
	 * which bypasses the XGXS block.
	 * If possible, check PHY's XGXS link status except when using
	 * MAC loopback.
	 */
	return (efx->loopback_mode == LOOPBACK_XGMII ||
		falcon_xgxs_link_ok(efx)) &&
		(!(efx->mdio.mmds & (1 << MDIO_MMD_PHYXS)) ||
		 LOOPBACK_INTERNAL(efx) ||
		 ef4_mdio_phyxgxs_lane_sync(efx));
}