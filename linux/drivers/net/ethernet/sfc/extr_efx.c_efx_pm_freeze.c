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
struct efx_nic {scalar_t__ state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ STATE_DISABLED ; 
 scalar_t__ STATE_UNINIT ; 
 struct efx_nic* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  efx_device_detach_sync (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_disable_interrupts (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_stop_all (struct efx_nic*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int efx_pm_freeze(struct device *dev)
{
	struct efx_nic *efx = dev_get_drvdata(dev);

	rtnl_lock();

	if (efx->state != STATE_DISABLED) {
		efx->state = STATE_UNINIT;

		efx_device_detach_sync(efx);

		efx_stop_all(efx);
		efx_disable_interrupts(efx);
	}

	rtnl_unlock();

	return 0;
}