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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_D_TXBLK_BASE ; 
 int /*<<< orphan*/  AR_D_TXBLK_WRITE_COMMAND ; 
 int /*<<< orphan*/  AR_D_TXBLK_WRITE_DCU ; 
 int /*<<< orphan*/  AR_D_TXBLK_WRITE_SLICE ; 
 int ATH9K_HW_BIT_IN_SLICE ; 
 int ATH9K_HW_SLICE_PER_DCU ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  PS ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 

void ath9k_hw_set_tx_filter(struct ath_hw *ah, u8 destidx, bool set)
{
	int dcu_idx;
	u32 filter;

	for (dcu_idx = 0; dcu_idx < 10; dcu_idx++) {
		filter = SM(set, AR_D_TXBLK_WRITE_COMMAND);
		filter |= SM(dcu_idx, AR_D_TXBLK_WRITE_DCU);
		filter |= SM((destidx / ATH9K_HW_SLICE_PER_DCU),
			     AR_D_TXBLK_WRITE_SLICE);
		filter |= BIT(destidx % ATH9K_HW_BIT_IN_SLICE);
		ath_dbg(ath9k_hw_common(ah), PS,
			"DCU%d staid %d set %d txfilter %08x\n",
			dcu_idx, destidx, set, filter);
		REG_WRITE(ah, AR_D_TXBLK_BASE, filter);
	}
}