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
struct e1000_hw {scalar_t__ hw_addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int flags2; } ;

/* Variables and functions */
 int FLAG2_PCIM2PCI_ARBITER_WA ; 
 int /*<<< orphan*/  __ew32_prepare (struct e1000_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void __ew32(struct e1000_hw *hw, unsigned long reg, u32 val)
{
	if (hw->adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
		__ew32_prepare(hw);

	writel(val, hw->hw_addr + reg);
}