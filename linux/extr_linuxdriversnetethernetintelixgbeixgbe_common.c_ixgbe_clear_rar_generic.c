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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* clear_vmdq ) (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ num_rar_entries; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CLEAR_VMDQ_ALL ; 
 int /*<<< orphan*/  IXGBE_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  IXGBE_RAH (scalar_t__) ; 
 int IXGBE_RAH_AV ; 
 int /*<<< orphan*/  IXGBE_RAL (scalar_t__) ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,scalar_t__,int /*<<< orphan*/ ) ; 

s32 ixgbe_clear_rar_generic(struct ixgbe_hw *hw, u32 index)
{
	u32 rar_high;
	u32 rar_entries = hw->mac.num_rar_entries;

	/* Make sure we are using a valid rar index range */
	if (index >= rar_entries) {
		hw_dbg(hw, "RAR index %d is out of range.\n", index);
		return IXGBE_ERR_INVALID_ARGUMENT;
	}

	/*
	 * Some parts put the VMDq setting in the extra RAH bits,
	 * so save everything except the lower 16 bits that hold part
	 * of the address and the address valid bit.
	 */
	rar_high = IXGBE_READ_REG(hw, IXGBE_RAH(index));
	rar_high &= ~(0x0000FFFF | IXGBE_RAH_AV);

	/* Clear the address valid bit and upper 16 bits of the address
	 * before clearing the lower bits. This way we aren't updating
	 * a live filter.
	 */
	IXGBE_WRITE_REG(hw, IXGBE_RAH(index), rar_high);
	IXGBE_WRITE_FLUSH(hw);
	IXGBE_WRITE_REG(hw, IXGBE_RAL(index), 0);

	/* clear VMDq pool/queue selection for this RAR */
	hw->mac.ops.clear_vmdq(hw, index, IXGBE_CLEAR_VMDQ_ALL);

	return 0;
}