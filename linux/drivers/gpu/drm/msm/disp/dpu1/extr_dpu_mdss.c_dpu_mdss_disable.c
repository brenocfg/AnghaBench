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
struct msm_mdss {int dummy; } ;
struct dss_module_power {int /*<<< orphan*/  num_clk; int /*<<< orphan*/  clk_config; } ;
struct dpu_mdss {int num_paths; int /*<<< orphan*/ * path; struct dss_module_power mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
 int /*<<< orphan*/  icc_set_bw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msm_dss_enable_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dpu_mdss* to_dpu_mdss (struct msm_mdss*) ; 

__attribute__((used)) static int dpu_mdss_disable(struct msm_mdss *mdss)
{
	struct dpu_mdss *dpu_mdss = to_dpu_mdss(mdss);
	struct dss_module_power *mp = &dpu_mdss->mp;
	int ret, i;

	ret = msm_dss_enable_clk(mp->clk_config, mp->num_clk, false);
	if (ret)
		DPU_ERROR("clock disable failed, ret:%d\n", ret);

	for (i = 0; i < dpu_mdss->num_paths; i++)
		icc_set_bw(dpu_mdss->path[i], 0, 0);

	return ret;
}