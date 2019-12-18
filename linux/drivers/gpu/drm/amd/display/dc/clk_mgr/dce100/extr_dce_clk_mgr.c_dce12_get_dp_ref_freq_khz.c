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
struct clk_mgr_internal {int dummy; } ;
struct clk_mgr {int /*<<< orphan*/  dprefclk_khz; } ;

/* Variables and functions */
 struct clk_mgr_internal* TO_CLK_MGR_INTERNAL (struct clk_mgr*) ; 
 int dce_adjust_dp_ref_freq_for_ss (struct clk_mgr_internal*,int /*<<< orphan*/ ) ; 

int dce12_get_dp_ref_freq_khz(struct clk_mgr *clk_mgr_base)
{
	struct clk_mgr_internal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	return dce_adjust_dp_ref_freq_for_ss(clk_mgr_dce, clk_mgr_base->dprefclk_khz);
}