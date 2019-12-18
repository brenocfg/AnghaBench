#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct dss_clk {scalar_t__ max_rate; scalar_t__ rate; } ;
struct TYPE_2__ {struct dss_clk* core_clk; } ;
struct dpu_kms {TYPE_1__ perf; } ;

/* Variables and functions */
 int msm_dss_clk_set_rate (struct dss_clk*,int) ; 

__attribute__((used)) static int _dpu_core_perf_set_core_clk_rate(struct dpu_kms *kms, u64 rate)
{
	struct dss_clk *core_clk = kms->perf.core_clk;

	if (core_clk->max_rate && (rate > core_clk->max_rate))
		rate = core_clk->max_rate;

	core_clk->rate = rate;
	return msm_dss_clk_set_rate(core_clk, 1);
}