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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int /*<<< orphan*/  reset_task; int /*<<< orphan*/  flags; struct e1000_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGB_FLAG_FQTSS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ e1000_i210 ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enable_fqtss(struct igb_adapter *adapter, bool enable)
{
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;

	WARN_ON(hw->mac.type != e1000_i210);

	if (enable)
		adapter->flags |= IGB_FLAG_FQTSS;
	else
		adapter->flags &= ~IGB_FLAG_FQTSS;

	if (netif_running(netdev))
		schedule_work(&adapter->reset_task);
}