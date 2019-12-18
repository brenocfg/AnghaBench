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
struct e1000_adapter {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  __e1000_vlan_mode (struct e1000_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_vlan_mode(struct net_device *netdev,
			    netdev_features_t features)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_disable(adapter);

	__e1000_vlan_mode(adapter, features);

	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_enable(adapter);
}