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
struct efx_nic {TYPE_1__* type; int /*<<< orphan*/  net_dev; scalar_t__ txq_entries; scalar_t__ rxq_entries; } ;
struct TYPE_2__ {int (* vswitching_probe ) (struct efx_nic*) ;int /*<<< orphan*/  (* vswitching_remove ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ EFX_DEFAULT_DMAQ_SIZE ; 
 scalar_t__ EFX_RXQ_MIN_ENT ; 
 scalar_t__ EFX_TXQ_MIN_ENT (struct efx_nic*) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int efx_probe_channels (struct efx_nic*) ; 
 int efx_probe_filters (struct efx_nic*) ; 
 int efx_probe_nic (struct efx_nic*) ; 
 int efx_probe_port (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_filters (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_nic (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_port (struct efx_nic*) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  probe ; 
 int stub1 (struct efx_nic*) ; 
 int /*<<< orphan*/  stub2 (struct efx_nic*) ; 

__attribute__((used)) static int efx_probe_all(struct efx_nic *efx)
{
	int rc;

	rc = efx_probe_nic(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "failed to create NIC\n");
		goto fail1;
	}

	rc = efx_probe_port(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "failed to create port\n");
		goto fail2;
	}

	BUILD_BUG_ON(EFX_DEFAULT_DMAQ_SIZE < EFX_RXQ_MIN_ENT);
	if (WARN_ON(EFX_DEFAULT_DMAQ_SIZE < EFX_TXQ_MIN_ENT(efx))) {
		rc = -EINVAL;
		goto fail3;
	}
	efx->rxq_entries = efx->txq_entries = EFX_DEFAULT_DMAQ_SIZE;

#ifdef CONFIG_SFC_SRIOV
	rc = efx->type->vswitching_probe(efx);
	if (rc) /* not fatal; the PF will still work fine */
		netif_warn(efx, probe, efx->net_dev,
			   "failed to setup vswitching rc=%d;"
			   " VFs may not function\n", rc);
#endif

	rc = efx_probe_filters(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev,
			  "failed to create filter tables\n");
		goto fail4;
	}

	rc = efx_probe_channels(efx);
	if (rc)
		goto fail5;

	return 0;

 fail5:
	efx_remove_filters(efx);
 fail4:
#ifdef CONFIG_SFC_SRIOV
	efx->type->vswitching_remove(efx);
#endif
 fail3:
	efx_remove_port(efx);
 fail2:
	efx_remove_nic(efx);
 fail1:
	return rc;
}