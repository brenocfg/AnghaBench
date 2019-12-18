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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct atl2_adapter {int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATL2_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATL2_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 int /*<<< orphan*/  __atl2_vlan_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl2_irq_disable (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_irq_enable (struct atl2_adapter*) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void atl2_vlan_mode(struct net_device *netdev,
	netdev_features_t features)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);
	u32 ctrl;

	atl2_irq_disable(adapter);

	ctrl = ATL2_READ_REG(&adapter->hw, REG_MAC_CTRL);
	__atl2_vlan_mode(features, &ctrl);
	ATL2_WRITE_REG(&adapter->hw, REG_MAC_CTRL, ctrl);

	atl2_irq_enable(adapter);
}