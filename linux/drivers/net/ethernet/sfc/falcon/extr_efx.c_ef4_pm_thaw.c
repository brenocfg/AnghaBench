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
struct ef4_nic {scalar_t__ state; int /*<<< orphan*/  reset_work; TYPE_2__* type; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* resume_wol ) (struct ef4_nic*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* reconfigure ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 scalar_t__ STATE_DISABLED ; 
 scalar_t__ STATE_READY ; 
 struct ef4_nic* dev_get_drvdata (struct device*) ; 
 int ef4_enable_interrupts (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_start_all (struct ef4_nic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_workqueue ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub2 (struct ef4_nic*) ; 

__attribute__((used)) static int ef4_pm_thaw(struct device *dev)
{
	int rc;
	struct ef4_nic *efx = dev_get_drvdata(dev);

	rtnl_lock();

	if (efx->state != STATE_DISABLED) {
		rc = ef4_enable_interrupts(efx);
		if (rc)
			goto fail;

		mutex_lock(&efx->mac_lock);
		efx->phy_op->reconfigure(efx);
		mutex_unlock(&efx->mac_lock);

		ef4_start_all(efx);

		netif_device_attach(efx->net_dev);

		efx->state = STATE_READY;

		efx->type->resume_wol(efx);
	}

	rtnl_unlock();

	/* Reschedule any quenched resets scheduled during ef4_pm_freeze() */
	queue_work(reset_workqueue, &efx->reset_work);

	return 0;

fail:
	rtnl_unlock();

	return rc;
}