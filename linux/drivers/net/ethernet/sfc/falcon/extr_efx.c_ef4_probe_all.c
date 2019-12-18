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
struct ef4_nic {int /*<<< orphan*/  net_dev; scalar_t__ txq_entries; scalar_t__ rxq_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ EF4_DEFAULT_DMAQ_SIZE ; 
 scalar_t__ EF4_RXQ_MIN_ENT ; 
 scalar_t__ EF4_TXQ_MIN_ENT (struct ef4_nic*) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int ef4_probe_channels (struct ef4_nic*) ; 
 int ef4_probe_filters (struct ef4_nic*) ; 
 int ef4_probe_nic (struct ef4_nic*) ; 
 int ef4_probe_port (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_remove_filters (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_remove_nic (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_remove_port (struct ef4_nic*) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int ef4_probe_all(struct ef4_nic *efx)
{
	int rc;

	rc = ef4_probe_nic(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "failed to create NIC\n");
		goto fail1;
	}

	rc = ef4_probe_port(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "failed to create port\n");
		goto fail2;
	}

	BUILD_BUG_ON(EF4_DEFAULT_DMAQ_SIZE < EF4_RXQ_MIN_ENT);
	if (WARN_ON(EF4_DEFAULT_DMAQ_SIZE < EF4_TXQ_MIN_ENT(efx))) {
		rc = -EINVAL;
		goto fail3;
	}
	efx->rxq_entries = efx->txq_entries = EF4_DEFAULT_DMAQ_SIZE;

	rc = ef4_probe_filters(efx);
	if (rc) {
		netif_err(efx, probe, efx->net_dev,
			  "failed to create filter tables\n");
		goto fail4;
	}

	rc = ef4_probe_channels(efx);
	if (rc)
		goto fail5;

	return 0;

 fail5:
	ef4_remove_filters(efx);
 fail4:
 fail3:
	ef4_remove_port(efx);
 fail2:
	ef4_remove_nic(efx);
 fail1:
	return rc;
}