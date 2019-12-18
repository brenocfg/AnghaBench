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
struct ef4_nic {int port_enabled; int /*<<< orphan*/  mac_work; int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  mac_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_ASSERT_RESET_SERIALISED (struct ef4_nic*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ef4_selftest_async_cancel (struct ef4_nic*) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ef4_stop_port(struct ef4_nic *efx)
{
	netif_dbg(efx, ifdown, efx->net_dev, "stop port\n");

	EF4_ASSERT_RESET_SERIALISED(efx);

	mutex_lock(&efx->mac_lock);
	efx->port_enabled = false;
	mutex_unlock(&efx->mac_lock);

	/* Serialise against ef4_set_multicast_list() */
	netif_addr_lock_bh(efx->net_dev);
	netif_addr_unlock_bh(efx->net_dev);

	cancel_delayed_work_sync(&efx->monitor_work);
	ef4_selftest_async_cancel(efx);
	cancel_work_sync(&efx->mac_work);
}