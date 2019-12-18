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
struct ef4_nic {int port_initialized; int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  filter_sem; int /*<<< orphan*/  net_dev; TYPE_2__* phy_op; TYPE_1__* type; } ;
typedef  enum reset_type { ____Placeholder_reset_type } reset_type ;
struct TYPE_4__ {int (* init ) (struct ef4_nic*) ;int (* reconfigure ) (struct ef4_nic*) ;} ;
struct TYPE_3__ {int (* init ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_ASSERT_RESET_SERIALISED (struct ef4_nic*) ; 
 int EPERM ; 
 int RESET_TYPE_DATAPATH ; 
 int RESET_TYPE_INVISIBLE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int ef4_enable_interrupts (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_restore_filters (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_start_all (struct ef4_nic*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct ef4_nic*) ; 
 int stub2 (struct ef4_nic*) ; 
 int stub3 (struct ef4_nic*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ef4_reset_up(struct ef4_nic *efx, enum reset_type method, bool ok)
{
	int rc;

	EF4_ASSERT_RESET_SERIALISED(efx);

	/* Ensure that SRAM is initialised even if we're disabling the device */
	rc = efx->type->init(efx);
	if (rc) {
		netif_err(efx, drv, efx->net_dev, "failed to initialise NIC\n");
		goto fail;
	}

	if (!ok)
		goto fail;

	if (efx->port_initialized && method != RESET_TYPE_INVISIBLE &&
	    method != RESET_TYPE_DATAPATH) {
		rc = efx->phy_op->init(efx);
		if (rc)
			goto fail;
		rc = efx->phy_op->reconfigure(efx);
		if (rc && rc != -EPERM)
			netif_err(efx, drv, efx->net_dev,
				  "could not restore PHY settings\n");
	}

	rc = ef4_enable_interrupts(efx);
	if (rc)
		goto fail;

	down_read(&efx->filter_sem);
	ef4_restore_filters(efx);
	up_read(&efx->filter_sem);

	mutex_unlock(&efx->mac_lock);

	ef4_start_all(efx);

	return 0;

fail:
	efx->port_initialized = false;

	mutex_unlock(&efx->mac_lock);

	return rc;
}