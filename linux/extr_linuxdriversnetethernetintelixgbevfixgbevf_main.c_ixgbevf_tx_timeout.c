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
struct ixgbevf_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbevf_tx_timeout_reset (struct ixgbevf_adapter*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbevf_tx_timeout(struct net_device *netdev)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);

	ixgbevf_tx_timeout_reset(adapter);
}