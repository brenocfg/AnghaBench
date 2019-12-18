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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ hw_addr; } ;
struct atlx_adapter {int /*<<< orphan*/  lock; TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 scalar_t__ REG_MAC_CTRL ; 
 int /*<<< orphan*/  __atlx_vlan_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct atlx_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atlx_vlan_mode(struct net_device *netdev,
	netdev_features_t features)
{
	struct atlx_adapter *adapter = netdev_priv(netdev);
	unsigned long flags;
	u32 ctrl;

	spin_lock_irqsave(&adapter->lock, flags);
	/* atlx_irq_disable(adapter); FIXME: confirm/remove */
	ctrl = ioread32(adapter->hw.hw_addr + REG_MAC_CTRL);
	__atlx_vlan_mode(features, &ctrl);
	iowrite32(ctrl, adapter->hw.hw_addr + REG_MAC_CTRL);
	/* atlx_irq_enable(adapter); FIXME */
	spin_unlock_irqrestore(&adapter->lock, flags);
}