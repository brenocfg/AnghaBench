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
struct efx_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ptp_set_ts_sync_events ) (struct efx_nic*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 scalar_t__ efx_ptp_restart (struct efx_nic*) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,int,int) ; 

void efx_ptp_start_datapath(struct efx_nic *efx)
{
	if (efx_ptp_restart(efx))
		netif_err(efx, drv, efx->net_dev, "Failed to restart PTP.\n");
	/* re-enable timestamping if it was previously enabled */
	if (efx->type->ptp_set_ts_sync_events)
		efx->type->ptp_set_ts_sync_events(efx, true, true);
}