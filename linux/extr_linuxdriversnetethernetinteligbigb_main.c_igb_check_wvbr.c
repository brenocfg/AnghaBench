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
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int /*<<< orphan*/  wvbr; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_WVBR ; 
#define  e1000_82576 129 
#define  e1000_i350 128 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_check_wvbr(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 wvbr = 0;

	switch (hw->mac.type) {
	case e1000_82576:
	case e1000_i350:
		wvbr = rd32(E1000_WVBR);
		if (!wvbr)
			return;
		break;
	default:
		break;
	}

	adapter->wvbr |= wvbr;
}