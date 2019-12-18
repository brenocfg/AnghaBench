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
typedef  int u32 ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int flags; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_RCTL_EN ; 
 int FLAG_RESTART_NOW ; 
 int FLAG_RX_NEEDS_RESTART ; 
 int /*<<< orphan*/  RCTL ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000e_enable_receives(struct e1000_adapter *adapter)
{
	/* make sure the receive unit is started */
	if ((adapter->flags & FLAG_RX_NEEDS_RESTART) &&
	    (adapter->flags & FLAG_RESTART_NOW)) {
		struct e1000_hw *hw = &adapter->hw;
		u32 rctl = er32(RCTL);

		ew32(RCTL, rctl | E1000_RCTL_EN);
		adapter->flags &= ~FLAG_RESTART_NOW;
	}
}