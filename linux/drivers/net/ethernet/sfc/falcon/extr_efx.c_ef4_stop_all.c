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
struct ef4_nic {int /*<<< orphan*/  net_dev; TYPE_1__* type; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  port_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_stats ) (struct ef4_nic*) ;int /*<<< orphan*/  (* update_stats ) (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pull_stats ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_ASSERT_RESET_SERIALISED (struct ef4_nic*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ef4_stop_datapath (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_stop_port (struct ef4_nic*) ; 
 scalar_t__ netif_device_present (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub2 (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct ef4_nic*) ; 

__attribute__((used)) static void ef4_stop_all(struct ef4_nic *efx)
{
	EF4_ASSERT_RESET_SERIALISED(efx);

	/* port_enabled can be read safely under the rtnl lock */
	if (!efx->port_enabled)
		return;

	/* update stats before we go down so we can accurately count
	 * rx_nodesc_drops
	 */
	efx->type->pull_stats(efx);
	spin_lock_bh(&efx->stats_lock);
	efx->type->update_stats(efx, NULL, NULL);
	spin_unlock_bh(&efx->stats_lock);
	efx->type->stop_stats(efx);
	ef4_stop_port(efx);

	/* Stop the kernel transmit interface.  This is only valid if
	 * the device is stopped or detached; otherwise the watchdog
	 * may fire immediately.
	 */
	WARN_ON(netif_running(efx->net_dev) &&
		netif_device_present(efx->net_dev));
	netif_tx_disable(efx->net_dev);

	ef4_stop_datapath(efx);
}