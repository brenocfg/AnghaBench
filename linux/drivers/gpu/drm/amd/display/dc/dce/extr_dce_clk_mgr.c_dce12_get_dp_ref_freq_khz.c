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
struct dce_clk_mgr {int /*<<< orphan*/  dprefclk_khz; } ;
struct clk_mgr {int dummy; } ;

/* Variables and functions */
 struct dce_clk_mgr* TO_DCE_CLK_MGR (struct clk_mgr*) ; 
 int clk_mgr_adjust_dp_ref_freq_for_ss (struct dce_clk_mgr*,int /*<<< orphan*/ ) ; 

int dce12_get_dp_ref_freq_khz(struct clk_mgr *clk_mgr)
{
	struct dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);

	return clk_mgr_adjust_dp_ref_freq_for_ss(clk_mgr_dce, clk_mgr_dce->dprefclk_khz);
}