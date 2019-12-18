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
struct net_device {int dummy; } ;
struct ef4_nic {int /*<<< orphan*/  mac_work; int /*<<< orphan*/  workqueue; scalar_t__ port_enabled; } ;

/* Variables and functions */
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ef4_set_rx_mode(struct net_device *net_dev)
{
	struct ef4_nic *efx = netdev_priv(net_dev);

	if (efx->port_enabled)
		queue_work(efx->workqueue, &efx->mac_work);
	/* Otherwise ef4_start_port() will do this */
}