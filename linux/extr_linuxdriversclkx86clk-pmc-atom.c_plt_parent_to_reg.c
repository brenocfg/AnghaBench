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
 int PMC_CLK_FREQ_PLL ; 
 int PMC_CLK_FREQ_XTAL ; 

__attribute__((used)) static inline int plt_parent_to_reg(int index)
{
	switch (index) {
	default:
	case 0:
		return PMC_CLK_FREQ_XTAL;
	case 1:
		return PMC_CLK_FREQ_PLL;
	}
}