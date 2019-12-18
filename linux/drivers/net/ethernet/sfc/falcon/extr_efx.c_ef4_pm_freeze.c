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
struct ef4_nic {scalar_t__ state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ STATE_DISABLED ; 
 scalar_t__ STATE_UNINIT ; 
 struct ef4_nic* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ef4_device_detach_sync (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_disable_interrupts (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_stop_all (struct ef4_nic*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int ef4_pm_freeze(struct device *dev)
{
	struct ef4_nic *efx = dev_get_drvdata(dev);

	rtnl_lock();

	if (efx->state != STATE_DISABLED) {
		efx->state = STATE_UNINIT;

		ef4_device_detach_sync(efx);

		ef4_stop_all(efx);
		ef4_disable_interrupts(efx);
	}

	rtnl_unlock();

	return 0;
}