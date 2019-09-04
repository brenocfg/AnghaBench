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
struct ksz_hw {scalar_t__ io; int /*<<< orphan*/  intr_set; int /*<<< orphan*/  intr_mask; int /*<<< orphan*/  intr_blocked; } ;

/* Variables and functions */
 scalar_t__ KS884X_INTERRUPTS_ENABLE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void hw_dis_intr(struct ksz_hw *hw)
{
	hw->intr_blocked = hw->intr_mask;
	writel(0, hw->io + KS884X_INTERRUPTS_ENABLE);
	hw->intr_set = readl(hw->io + KS884X_INTERRUPTS_ENABLE);
}