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
struct ef4_nic {scalar_t__ state; int /*<<< orphan*/  stats_lock; TYPE_1__* type; int /*<<< orphan*/  monitor_work; int /*<<< orphan*/  workqueue; scalar_t__ reset_pending; int /*<<< orphan*/  net_dev; scalar_t__ port_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_stats ) (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pull_stats ) (struct ef4_nic*) ;int /*<<< orphan*/  (* start_stats ) (struct ef4_nic*) ;int /*<<< orphan*/ * monitor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EF4_ASSERT_RESET_SERIALISED (struct ef4_nic*) ; 
 scalar_t__ STATE_DISABLED ; 
 int /*<<< orphan*/  ef4_monitor_interval ; 
 int /*<<< orphan*/  ef4_start_datapath (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_start_port (struct ef4_nic*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub2 (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub3 (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ef4_start_all(struct ef4_nic *efx)
{
	EF4_ASSERT_RESET_SERIALISED(efx);
	BUG_ON(efx->state == STATE_DISABLED);

	/* Check that it is appropriate to restart the interface. All
	 * of these flags are safe to read under just the rtnl lock */
	if (efx->port_enabled || !netif_running(efx->net_dev) ||
	    efx->reset_pending)
		return;

	ef4_start_port(efx);
	ef4_start_datapath(efx);

	/* Start the hardware monitor if there is one */
	if (efx->type->monitor != NULL)
		queue_delayed_work(efx->workqueue, &efx->monitor_work,
				   ef4_monitor_interval);

	efx->type->start_stats(efx);
	efx->type->pull_stats(efx);
	spin_lock_bh(&efx->stats_lock);
	efx->type->update_stats(efx, NULL, NULL);
	spin_unlock_bh(&efx->stats_lock);
}