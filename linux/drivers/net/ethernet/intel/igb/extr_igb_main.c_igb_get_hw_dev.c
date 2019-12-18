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
struct igb_adapter {struct net_device* netdev; } ;
struct e1000_hw {struct igb_adapter* back; } ;

/* Variables and functions */

struct net_device *igb_get_hw_dev(struct e1000_hw *hw)
{
	struct igb_adapter *adapter = hw->back;
	return adapter->netdev;
}