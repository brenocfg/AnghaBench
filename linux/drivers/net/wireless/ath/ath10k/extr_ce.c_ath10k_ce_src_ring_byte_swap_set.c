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
typedef  int u32 ;
struct ath10k_hw_ce_ctrl1 {int addr; TYPE_2__* src_ring; } ;
struct ath10k {TYPE_1__* hw_ce_regs; } ;
struct TYPE_4__ {int mask; } ;
struct TYPE_3__ {struct ath10k_hw_ce_ctrl1* ctrl1_regs; } ;

/* Variables and functions */
 int ath10k_ce_read32 (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_ce_write32 (struct ath10k*,int,int) ; 
 int ath10k_set_ring_byte (unsigned int,TYPE_2__*) ; 

__attribute__((used)) static inline void ath10k_ce_src_ring_byte_swap_set(struct ath10k *ar,
						    u32 ce_ctrl_addr,
						    unsigned int n)
{
	struct ath10k_hw_ce_ctrl1 *ctrl_regs = ar->hw_ce_regs->ctrl1_regs;

	u32 ctrl1_addr = ath10k_ce_read32(ar, ce_ctrl_addr +
					  ctrl_regs->addr);

	ath10k_ce_write32(ar, ce_ctrl_addr + ctrl_regs->addr,
			  (ctrl1_addr & ~(ctrl_regs->src_ring->mask)) |
			  ath10k_set_ring_byte(n, ctrl_regs->src_ring));
}