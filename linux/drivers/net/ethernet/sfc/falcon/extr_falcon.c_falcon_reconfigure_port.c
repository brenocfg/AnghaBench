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
struct ef4_nic {TYPE_1__* phy_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reconfigure ) (struct ef4_nic*) ;int /*<<< orphan*/  (* poll ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EF4_REV_FALCON_B0 ; 
 scalar_t__ LOOPBACK_INTERNAL (struct ef4_nic*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ef4_link_status_changed (struct ef4_nic*) ; 
 scalar_t__ ef4_nic_rev (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_deconfigure_mac_wrapper (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_loopback_link_poll (struct ef4_nic*) ; 
 int falcon_reconfigure_xmac (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_reset_macs (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_start_nic_stats (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_stop_nic_stats (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub2 (struct ef4_nic*) ; 

__attribute__((used)) static int falcon_reconfigure_port(struct ef4_nic *efx)
{
	int rc;

	WARN_ON(ef4_nic_rev(efx) > EF4_REV_FALCON_B0);

	/* Poll the PHY link state *before* reconfiguring it. This means we
	 * will pick up the correct speed (in loopback) to select the correct
	 * MAC.
	 */
	if (LOOPBACK_INTERNAL(efx))
		falcon_loopback_link_poll(efx);
	else
		efx->phy_op->poll(efx);

	falcon_stop_nic_stats(efx);
	falcon_deconfigure_mac_wrapper(efx);

	falcon_reset_macs(efx);

	efx->phy_op->reconfigure(efx);
	rc = falcon_reconfigure_xmac(efx);
	BUG_ON(rc);

	falcon_start_nic_stats(efx);

	/* Synchronise efx->link_state with the kernel */
	ef4_link_status_changed(efx);

	return 0;
}