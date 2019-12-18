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
typedef  int u32 ;
struct TYPE_2__ {int san_mac_rar_index; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  IXGBE_MPSAR_HI (int) ; 
 int /*<<< orphan*/  IXGBE_MPSAR_LO (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 ixgbe_set_vmdq_san_mac_generic(struct ixgbe_hw *hw, u32 vmdq)
{
	u32 rar = hw->mac.san_mac_rar_index;

	if (vmdq < 32) {
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_LO(rar), BIT(vmdq));
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_HI(rar), 0);
	} else {
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_LO(rar), 0);
		IXGBE_WRITE_REG(hw, IXGBE_MPSAR_HI(rar), BIT(vmdq - 32));
	}

	return 0;
}