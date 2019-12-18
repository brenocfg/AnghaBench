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
struct ksz_hw {scalar_t__ io; int /*<<< orphan*/  intr_set; } ;

/* Variables and functions */
 scalar_t__ KS884X_INTERRUPTS_ENABLE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void hw_set_intr(struct ksz_hw *hw, uint interrupt)
{
	hw->intr_set = interrupt;
	writel(interrupt, hw->io + KS884X_INTERRUPTS_ENABLE);
}