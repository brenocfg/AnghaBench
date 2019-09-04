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
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PFMBMEM (scalar_t__) ; 
 scalar_t__ IXGBE_VFMAILBOX_SIZE ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_ARRAY (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_vf_clear_mbx(struct ixgbe_adapter *adapter, u32 vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 word;

	/* Clear VF's mailbox memory */
	for (word = 0; word < IXGBE_VFMAILBOX_SIZE; word++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_PFMBMEM(vf), word, 0);

	IXGBE_WRITE_FLUSH(hw);
}