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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IGB_MAC_STATE_QUEUE_STEERING ; 
 scalar_t__ e1000_i210 ; 
 int igb_add_mac_filter_flags (struct igb_adapter*,int const*,int,int) ; 

int igb_add_mac_steering_filter(struct igb_adapter *adapter,
				const u8 *addr, u8 queue, u8 flags)
{
	struct e1000_hw *hw = &adapter->hw;

	/* In theory, this should be supported on 82575 as well, but
	 * that part wasn't easily accessible during development.
	 */
	if (hw->mac.type != e1000_i210)
		return -EOPNOTSUPP;

	return igb_add_mac_filter_flags(adapter, addr, queue,
					IGB_MAC_STATE_QUEUE_STEERING | flags);
}