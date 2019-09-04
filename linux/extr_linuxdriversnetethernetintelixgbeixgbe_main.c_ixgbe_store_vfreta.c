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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {scalar_t__* rss_indir_tbl; int /*<<< orphan*/  num_rx_pools; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PFVFRETA (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 size_t ixgbe_rss_indir_tbl_entries (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_store_vfreta(struct ixgbe_adapter *adapter)
{
	u32 i, reta_entries = ixgbe_rss_indir_tbl_entries(adapter);
	struct ixgbe_hw *hw = &adapter->hw;
	u32 vfreta = 0;

	/* Write redirection table to HW */
	for (i = 0; i < reta_entries; i++) {
		u16 pool = adapter->num_rx_pools;

		vfreta |= (u32)adapter->rss_indir_tbl[i] << (i & 0x3) * 8;
		if ((i & 3) != 3)
			continue;

		while (pool--)
			IXGBE_WRITE_REG(hw,
					IXGBE_PFVFRETA(i >> 2, VMDQ_P(pool)),
					vfreta);
		vfreta = 0;
	}
}