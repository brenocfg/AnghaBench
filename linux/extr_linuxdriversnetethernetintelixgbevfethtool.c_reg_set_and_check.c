#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  hw_addr; } ;
struct ixgbevf_adapter {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ IXGBE_REMOVED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_write_reg (TYPE_1__*,int,int) ; 
 int ixgbevf_read_reg (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 

__attribute__((used)) static bool reg_set_and_check(struct ixgbevf_adapter *adapter, u64 *data,
			      int reg, u32 mask, u32 write)
{
	u32 val, before;

	if (IXGBE_REMOVED(adapter->hw.hw_addr)) {
		*data = 1;
		return true;
	}
	before = ixgbevf_read_reg(&adapter->hw, reg);
	ixgbe_write_reg(&adapter->hw, reg, write & mask);
	val = ixgbevf_read_reg(&adapter->hw, reg);
	if ((write & mask) != (val & mask)) {
		pr_err("set/check reg %04X test failed: got 0x%08X expected 0x%08X\n",
		       reg, (val & mask), write & mask);
		*data = reg;
		ixgbe_write_reg(&adapter->hw, reg, before);
		return true;
	}
	ixgbe_write_reg(&adapter->hw, reg, before);
	return false;
}