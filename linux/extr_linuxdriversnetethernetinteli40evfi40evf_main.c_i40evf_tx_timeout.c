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
struct i40evf_adapter {int /*<<< orphan*/  tx_timeout_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40evf_schedule_reset (struct i40evf_adapter*) ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void i40evf_tx_timeout(struct net_device *netdev)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);

	adapter->tx_timeout_count++;
	i40evf_schedule_reset(adapter);
}