#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  time; int /*<<< orphan*/  active; } ;
struct msm_gpu {int perfcntr_active; int /*<<< orphan*/  perf_lock; scalar_t__ totaltime; scalar_t__ activetime; TYPE_2__ last_sample; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  msm_gpu_active (struct msm_gpu*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_hw_cntrs (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void msm_gpu_perfcntr_start(struct msm_gpu *gpu)
{
	unsigned long flags;

	pm_runtime_get_sync(&gpu->pdev->dev);

	spin_lock_irqsave(&gpu->perf_lock, flags);
	/* we could dynamically enable/disable perfcntr registers too.. */
	gpu->last_sample.active = msm_gpu_active(gpu);
	gpu->last_sample.time = ktime_get();
	gpu->activetime = gpu->totaltime = 0;
	gpu->perfcntr_active = true;
	update_hw_cntrs(gpu, 0, NULL);
	spin_unlock_irqrestore(&gpu->perf_lock, flags);
}