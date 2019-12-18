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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct ath10k {TYPE_1__* hw_ce_regs; } ;
struct TYPE_2__ {int dr_base_addr_hi; } ;

/* Variables and functions */
 int CE_DESC_ADDR_HI_MASK ; 
 int ath10k_ce_read32 (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_ce_write32 (struct ath10k*,int,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_ce_set_dest_ring_base_addr_hi(struct ath10k *ar,
						 u32 ce_ctrl_addr,
						 u64 addr)
{
	u32 addr_hi = upper_32_bits(addr) & CE_DESC_ADDR_HI_MASK;
	u32 reg_value;

	reg_value = ath10k_ce_read32(ar, ce_ctrl_addr +
				     ar->hw_ce_regs->dr_base_addr_hi);
	reg_value &= ~CE_DESC_ADDR_HI_MASK;
	reg_value |= addr_hi;
	ath10k_ce_write32(ar, ce_ctrl_addr +
			  ar->hw_ce_regs->dr_base_addr_hi, reg_value);
}