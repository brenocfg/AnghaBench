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
struct ehea_port {int /*<<< orphan*/  netdev; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  stats_work; int /*<<< orphan*/  reset_task; struct ehea_adapter* adapter; } ;
struct ehea_adapter {int /*<<< orphan*/  active_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehea_unregister_port (struct ehea_port*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehea_shutdown_single_port(struct ehea_port *port)
{
	struct ehea_adapter *adapter = port->adapter;

	cancel_work_sync(&port->reset_task);
	cancel_delayed_work_sync(&port->stats_work);
	unregister_netdev(port->netdev);
	ehea_unregister_port(port);
	kfree(port->mc_list);
	free_netdev(port->netdev);
	adapter->active_ports--;
}