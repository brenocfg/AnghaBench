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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct e1000_hw {int mac_type; } ;

/* Variables and functions */
 int E1000_RAH_AV ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  E1000_WRITE_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RA ; 

void e1000_rar_set(struct e1000_hw *hw, u8 *addr, u32 index)
{
	u32 rar_low, rar_high;

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32)addr[0] | ((u32)addr[1] << 8) |
		   ((u32)addr[2] << 16) | ((u32)addr[3] << 24));
	rar_high = ((u32)addr[4] | ((u32)addr[5] << 8));

	/* Disable Rx and flush all Rx frames before enabling RSS to avoid Rx
	 * unit hang.
	 *
	 * Description:
	 * If there are any Rx frames queued up or otherwise present in the HW
	 * before RSS is enabled, and then we enable RSS, the HW Rx unit will
	 * hang.  To work around this issue, we have to disable receives and
	 * flush out all Rx frames before we enable RSS. To do so, we modify we
	 * redirect all Rx traffic to manageability and then reset the HW.
	 * This flushes away Rx frames, and (since the redirections to
	 * manageability persists across resets) keeps new ones from coming in
	 * while we work.  Then, we clear the Address Valid AV bit for all MAC
	 * addresses and undo the re-direction to manageability.
	 * Now, frames are coming in again, but the MAC won't accept them, so
	 * far so good.  We now proceed to initialize RSS (if necessary) and
	 * configure the Rx unit.  Last, we re-enable the AV bits and continue
	 * on our merry way.
	 */
	switch (hw->mac_type) {
	default:
		/* Indicate to hardware the Address is Valid. */
		rar_high |= E1000_RAH_AV;
		break;
	}

	E1000_WRITE_REG_ARRAY(hw, RA, (index << 1), rar_low);
	E1000_WRITE_FLUSH();
	E1000_WRITE_REG_ARRAY(hw, RA, ((index << 1) + 1), rar_high);
	E1000_WRITE_FLUSH();
}