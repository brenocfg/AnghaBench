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
struct TYPE_2__ {int /*<<< orphan*/  devfreq; } ;
struct msm_gpu {TYPE_1__ devfreq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfreq_suspend_device (int /*<<< orphan*/ ) ; 
 int disable_axi (struct msm_gpu*) ; 
 int disable_clk (struct msm_gpu*) ; 
 int disable_pwrrail (struct msm_gpu*) ; 

int msm_gpu_pm_suspend(struct msm_gpu *gpu)
{
	int ret;

	DBG("%s", gpu->name);

	devfreq_suspend_device(gpu->devfreq.devfreq);

	ret = disable_axi(gpu);
	if (ret)
		return ret;

	ret = disable_clk(gpu);
	if (ret)
		return ret;

	ret = disable_pwrrail(gpu);
	if (ret)
		return ret;

	return 0;
}