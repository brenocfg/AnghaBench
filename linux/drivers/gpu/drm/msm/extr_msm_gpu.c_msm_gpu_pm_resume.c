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
struct msm_gpu {int needs_hw_init; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int enable_axi (struct msm_gpu*) ; 
 int enable_clk (struct msm_gpu*) ; 
 int enable_pwrrail (struct msm_gpu*) ; 
 int /*<<< orphan*/  msm_gpu_resume_devfreq (struct msm_gpu*) ; 

int msm_gpu_pm_resume(struct msm_gpu *gpu)
{
	int ret;

	DBG("%s", gpu->name);

	ret = enable_pwrrail(gpu);
	if (ret)
		return ret;

	ret = enable_clk(gpu);
	if (ret)
		return ret;

	ret = enable_axi(gpu);
	if (ret)
		return ret;

	msm_gpu_resume_devfreq(gpu);

	gpu->needs_hw_init = true;

	return 0;
}