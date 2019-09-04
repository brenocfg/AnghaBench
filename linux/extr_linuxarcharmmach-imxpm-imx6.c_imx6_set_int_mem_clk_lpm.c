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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_CGPR_INT_MEM_CLK_LPM ; 
 scalar_t__ CGPR ; 
 scalar_t__ ccm_base ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void imx6_set_int_mem_clk_lpm(bool enable)
{
	u32 val = readl_relaxed(ccm_base + CGPR);

	val &= ~BM_CGPR_INT_MEM_CLK_LPM;
	if (enable)
		val |= BM_CGPR_INT_MEM_CLK_LPM;
	writel_relaxed(val, ccm_base + CGPR);
}