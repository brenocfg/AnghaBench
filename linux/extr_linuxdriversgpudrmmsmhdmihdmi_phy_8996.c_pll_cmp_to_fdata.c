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
typedef  unsigned long u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PLL_CMP_CNT ; 
 int /*<<< orphan*/  do_div (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 pll_cmp_to_fdata(u32 pll_cmp, unsigned long ref_clk)
{
	u64 fdata = ((u64)pll_cmp) * ref_clk * 10;

	do_div(fdata, HDMI_PLL_CMP_CNT);

	return fdata;
}