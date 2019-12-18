#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {scalar_t__ (* validate_checksum ) (struct ixgbe_hw*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ixgbe_eeprom_test(struct ixgbe_adapter *adapter, u64 *data)
{
	struct ixgbe_hw *hw = &adapter->hw;
	if (hw->eeprom.ops.validate_checksum(hw, NULL))
		*data = 1;
	else
		*data = 0;
	return *data;
}