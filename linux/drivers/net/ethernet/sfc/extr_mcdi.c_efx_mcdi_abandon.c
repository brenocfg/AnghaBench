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
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_mcdi_iface {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ MCDI_MODE_FAIL ; 
 int /*<<< orphan*/  RESET_TYPE_MCDI_TIMEOUT ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xchg (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void efx_mcdi_abandon(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);

	if (xchg(&mcdi->mode, MCDI_MODE_FAIL) == MCDI_MODE_FAIL)
		return; /* it had already been done */
	netif_dbg(efx, hw, efx->net_dev, "MCDI is timing out; trying to recover\n");
	efx_schedule_reset(efx, RESET_TYPE_MCDI_TIMEOUT);
}