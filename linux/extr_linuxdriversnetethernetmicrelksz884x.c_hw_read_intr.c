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
struct ksz_hw {int intr_set; scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ KS884X_INTERRUPTS_STATUS ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline void hw_read_intr(struct ksz_hw *hw, uint *status)
{
	*status = readl(hw->io + KS884X_INTERRUPTS_STATUS);
	*status = *status & hw->intr_set;
}