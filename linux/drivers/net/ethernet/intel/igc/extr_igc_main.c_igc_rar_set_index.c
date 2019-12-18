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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct igc_hw {int dummy; } ;
struct igc_adapter {TYPE_1__* mac_table; struct igc_hw hw; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int state; size_t queue; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int IGC_MAC_STATE_IN_USE ; 
 int /*<<< orphan*/  IGC_RAH (size_t) ; 
 size_t IGC_RAH_AV ; 
 size_t IGC_RAH_POOL_1 ; 
 int /*<<< orphan*/  IGC_RAL (size_t) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 size_t le16_to_cpup (int /*<<< orphan*/ *) ; 
 size_t le32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wrfl () ; 

__attribute__((used)) static void igc_rar_set_index(struct igc_adapter *adapter, u32 index)
{
	u8 *addr = adapter->mac_table[index].addr;
	struct igc_hw *hw = &adapter->hw;
	u32 rar_low, rar_high;

	/* HW expects these to be in network order when they are plugged
	 * into the registers which are little endian.  In order to guarantee
	 * that ordering we need to do an leXX_to_cpup here in order to be
	 * ready for the byteswap that occurs with writel
	 */
	rar_low = le32_to_cpup((__le32 *)(addr));
	rar_high = le16_to_cpup((__le16 *)(addr + 4));

	/* Indicate to hardware the Address is Valid. */
	if (adapter->mac_table[index].state & IGC_MAC_STATE_IN_USE) {
		if (is_valid_ether_addr(addr))
			rar_high |= IGC_RAH_AV;

		rar_high |= IGC_RAH_POOL_1 <<
			adapter->mac_table[index].queue;
	}

	wr32(IGC_RAL(index), rar_low);
	wrfl();
	wr32(IGC_RAH(index), rar_high);
	wrfl();
}