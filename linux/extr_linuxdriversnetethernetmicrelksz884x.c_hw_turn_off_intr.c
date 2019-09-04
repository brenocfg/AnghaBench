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
typedef  int uint ;
typedef  int u32 ;
struct ksz_hw {int intr_set; scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ KS884X_INTERRUPTS_ENABLE ; 
 int /*<<< orphan*/  hw_dis_intr_bit (struct ksz_hw*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void hw_turn_off_intr(struct ksz_hw *hw, uint interrupt)
{
	u32 read_intr;

	read_intr = readl(hw->io + KS884X_INTERRUPTS_ENABLE);
	hw->intr_set = read_intr & ~interrupt;
	writel(hw->intr_set, hw->io + KS884X_INTERRUPTS_ENABLE);
	hw_dis_intr_bit(hw, interrupt);
}