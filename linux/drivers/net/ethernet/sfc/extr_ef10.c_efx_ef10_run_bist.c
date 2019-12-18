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
typedef  int /*<<< orphan*/  u32 ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int efx_ef10_poll_bist (struct efx_nic*) ; 
 int efx_ef10_start_bist (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ef10_run_bist(struct efx_nic *efx, u32 bist_type)
{
	int rc;

	netif_dbg(efx, drv, efx->net_dev, "starting BIST type %u\n", bist_type);

	rc = efx_ef10_start_bist(efx, bist_type);
	if (rc != 0)
		return rc;

	return efx_ef10_poll_bist(efx);
}