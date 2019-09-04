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
struct igbvf_adapter {int /*<<< orphan*/  reset_task; int /*<<< orphan*/  tx_timeout_count; } ;

/* Variables and functions */
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igbvf_tx_timeout(struct net_device *netdev)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of interrupt context */
	adapter->tx_timeout_count++;
	schedule_work(&adapter->reset_task);
}