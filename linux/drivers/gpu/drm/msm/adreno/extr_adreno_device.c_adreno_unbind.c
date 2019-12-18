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
struct msm_gpu {TYPE_1__* funcs; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct msm_gpu*) ;} ;

/* Variables and functions */
 struct msm_gpu* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_force_suspend (struct device*) ; 
 int /*<<< orphan*/  set_gpu_pdev (struct msm_gpu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*) ; 

__attribute__((used)) static void adreno_unbind(struct device *dev, struct device *master,
		void *data)
{
	struct msm_gpu *gpu = dev_get_drvdata(dev);

	pm_runtime_force_suspend(dev);
	gpu->funcs->destroy(gpu);

	set_gpu_pdev(dev_get_drvdata(master), NULL);
}