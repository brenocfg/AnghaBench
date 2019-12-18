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
struct dss_clk {scalar_t__ max_rate; } ;
struct drm_device {int dummy; } ;
struct dpu_mdss_cfg {int dummy; } ;
struct dpu_core_perf {scalar_t__ max_core_clk_rate; struct dss_clk* core_clk; struct dpu_mdss_cfg* catalog; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG (char*) ; 
 scalar_t__ DPU_PERF_DEFAULT_MAX_CORE_CLK_RATE ; 

int dpu_core_perf_init(struct dpu_core_perf *perf,
		struct drm_device *dev,
		struct dpu_mdss_cfg *catalog,
		struct dss_clk *core_clk)
{
	perf->dev = dev;
	perf->catalog = catalog;
	perf->core_clk = core_clk;

	perf->max_core_clk_rate = core_clk->max_rate;
	if (!perf->max_core_clk_rate) {
		DPU_DEBUG("optional max core clk rate, use default\n");
		perf->max_core_clk_rate = DPU_PERF_DEFAULT_MAX_CORE_CLK_RATE;
	}

	return 0;
}