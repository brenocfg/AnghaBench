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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_DELAY (struct ksz_hw*,scalar_t__) ; 
 scalar_t__ KS884X_ACC_DATA_0_OFFSET ; 
 scalar_t__ KS884X_ACC_DATA_4_OFFSET ; 
 scalar_t__ KS884X_IACR_OFFSET ; 
 int TABLE_SEL_SHIFT ; 
 int /*<<< orphan*/  hw_block_intr (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_restore_intr (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void sw_w_table_64(struct ksz_hw *hw, int table, u16 addr, u32 data_hi,
	u32 data_lo)
{
	u16 ctrl_addr;
	uint interrupt;

	ctrl_addr = ((table << TABLE_SEL_SHIFT) << 8) | addr;

	interrupt = hw_block_intr(hw);

	writel(data_hi, hw->io + KS884X_ACC_DATA_4_OFFSET);
	writel(data_lo, hw->io + KS884X_ACC_DATA_0_OFFSET);

	writew(ctrl_addr, hw->io + KS884X_IACR_OFFSET);
	HW_DELAY(hw, KS884X_IACR_OFFSET);

	hw_restore_intr(hw, interrupt);
}