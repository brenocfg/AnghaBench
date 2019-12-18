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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {size_t* rss_indir_tbl; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERETA (size_t) ; 
 int /*<<< orphan*/  IXGBE_RETA (size_t) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 size_t ixgbe_rss_indir_tbl_entries (struct ixgbe_adapter*) ; 

void ixgbe_store_reta(struct ixgbe_adapter *adapter)
{
	u32 i, reta_entries = ixgbe_rss_indir_tbl_entries(adapter);
	struct ixgbe_hw *hw = &adapter->hw;
	u32 reta = 0;
	u32 indices_multi;
	u8 *indir_tbl = adapter->rss_indir_tbl;

	/* Fill out the redirection table as follows:
	 *  - 82598:      8 bit wide entries containing pair of 4 bit RSS
	 *    indices.
	 *  - 82599/X540: 8 bit wide entries containing 4 bit RSS index
	 *  - X550:       8 bit wide entries containing 6 bit RSS index
	 */
	if (adapter->hw.mac.type == ixgbe_mac_82598EB)
		indices_multi = 0x11;
	else
		indices_multi = 0x1;

	/* Write redirection table to HW */
	for (i = 0; i < reta_entries; i++) {
		reta |= indices_multi * indir_tbl[i] << (i & 0x3) * 8;
		if ((i & 3) == 3) {
			if (i < 128)
				IXGBE_WRITE_REG(hw, IXGBE_RETA(i >> 2), reta);
			else
				IXGBE_WRITE_REG(hw, IXGBE_ERETA((i >> 2) - 32),
						reta);
			reta = 0;
		}
	}
}