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
struct e1000_hw {scalar_t__ mac_type; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 scalar_t__ e1000_82545 ; 
 scalar_t__ e1000_82546 ; 
 scalar_t__ e1000_ce4100 ; 

__attribute__((used)) static bool e1000_check_64k_bound(struct e1000_adapter *adapter, void *start,
				  unsigned long len)
{
	struct e1000_hw *hw = &adapter->hw;
	unsigned long begin = (unsigned long)start;
	unsigned long end = begin + len;

	/* First rev 82545 and 82546 need to not allow any memory
	 * write location to cross 64k boundary due to errata 23
	 */
	if (hw->mac_type == e1000_82545 ||
	    hw->mac_type == e1000_ce4100 ||
	    hw->mac_type == e1000_82546) {
		return ((begin ^ (end - 1)) >> 16) != 0 ? false : true;
	}

	return true;
}