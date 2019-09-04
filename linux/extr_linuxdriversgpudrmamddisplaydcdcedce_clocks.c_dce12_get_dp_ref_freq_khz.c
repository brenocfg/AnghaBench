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
struct dce_dccg {int dummy; } ;
struct dccg {int dummy; } ;

/* Variables and functions */
 struct dce_dccg* TO_DCE_CLOCKS (struct dccg*) ; 
 int dccg_adjust_dp_ref_freq_for_ss (struct dce_dccg*,int) ; 

__attribute__((used)) static int dce12_get_dp_ref_freq_khz(struct dccg *clk)
{
	struct dce_dccg *clk_dce = TO_DCE_CLOCKS(clk);

	return dccg_adjust_dp_ref_freq_for_ss(clk_dce, 600000);
}