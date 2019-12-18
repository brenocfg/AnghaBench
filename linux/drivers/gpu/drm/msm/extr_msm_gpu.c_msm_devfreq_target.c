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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct msm_gpu {int /*<<< orphan*/  core_clk; TYPE_1__* funcs; } ;
struct device {int dummy; } ;
struct dev_pm_opp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gpu_set_freq ) (struct msm_gpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 struct dev_pm_opp* devfreq_recommended_opp (struct device*,unsigned long*,int /*<<< orphan*/ ) ; 
 struct msm_gpu* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (struct device*) ; 

__attribute__((used)) static int msm_devfreq_target(struct device *dev, unsigned long *freq,
		u32 flags)
{
	struct msm_gpu *gpu = platform_get_drvdata(to_platform_device(dev));
	struct dev_pm_opp *opp;

	opp = devfreq_recommended_opp(dev, freq, flags);

	if (IS_ERR(opp))
		return PTR_ERR(opp);

	if (gpu->funcs->gpu_set_freq)
		gpu->funcs->gpu_set_freq(gpu, (u64)*freq);
	else
		clk_set_rate(gpu->core_clk, *freq);

	dev_pm_opp_put(opp);

	return 0;
}