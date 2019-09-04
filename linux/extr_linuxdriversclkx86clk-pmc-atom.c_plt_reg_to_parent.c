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

/* Variables and functions */
#define  PMC_CLK_FREQ_PLL 129 
#define  PMC_CLK_FREQ_XTAL 128 
 int PMC_MASK_CLK_FREQ ; 

__attribute__((used)) static inline int plt_reg_to_parent(int reg)
{
	switch (reg & PMC_MASK_CLK_FREQ) {
	default:
	case PMC_CLK_FREQ_XTAL:
		return 0;
	case PMC_CLK_FREQ_PLL:
		return 1;
	}
}