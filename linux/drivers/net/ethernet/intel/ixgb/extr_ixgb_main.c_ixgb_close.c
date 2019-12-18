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
struct ixgb_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgb_down (struct ixgb_adapter*,int) ; 
 int /*<<< orphan*/  ixgb_free_rx_resources (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_free_tx_resources (struct ixgb_adapter*) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ixgb_close(struct net_device *netdev)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);

	ixgb_down(adapter, true);

	ixgb_free_tx_resources(adapter);
	ixgb_free_rx_resources(adapter);

	return 0;
}