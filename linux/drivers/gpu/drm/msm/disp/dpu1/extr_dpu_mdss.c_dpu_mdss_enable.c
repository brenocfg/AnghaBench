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
struct dpu_mdss {struct dss_module_power mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
 int /*<<< orphan*/  dpu_mdss_icc_request_bw (struct msm_mdss*) ; 
 int msm_dss_enable_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dpu_mdss* to_dpu_mdss (struct msm_mdss*) ; 

__attribute__((used)) static int dpu_mdss_enable(struct msm_mdss *mdss)
{
	struct dpu_mdss *dpu_mdss = to_dpu_mdss(mdss);
	struct dss_module_power *mp = &dpu_mdss->mp;
	int ret;

	dpu_mdss_icc_request_bw(mdss);

	ret = msm_dss_enable_clk(mp->clk_config, mp->num_clk, true);
	if (ret)
		DPU_ERROR("clock enable failed, ret:%d\n", ret);

	return ret;
}