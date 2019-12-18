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
struct dss_video_pll {int /*<<< orphan*/  clkctrl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MOD (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void dss_dpll_enable_scp_clk(struct dss_video_pll *vpll)
{
	REG_MOD(vpll->clkctrl_base, 1, 14, 14); /* CIO_CLK_ICG */
}