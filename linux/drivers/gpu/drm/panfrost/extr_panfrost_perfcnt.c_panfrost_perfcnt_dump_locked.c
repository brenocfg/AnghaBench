#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct panfrost_device {TYPE_1__* perfcnt; } ;
struct TYPE_5__ {int start; } ;
struct TYPE_6__ {TYPE_2__ node; } ;
struct TYPE_4__ {int /*<<< orphan*/  dump_comp; TYPE_3__* bo; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GPU_CMD ; 
 int GPU_CMD_PERFCNT_SAMPLE ; 
 int /*<<< orphan*/  GPU_INT_CLEAR ; 
 int GPU_IRQ_CLEAN_CACHES_COMPLETED ; 
 int GPU_IRQ_PERFCNT_SAMPLE_COMPLETED ; 
 int /*<<< orphan*/  GPU_PERFCNT_BASE_HI ; 
 int /*<<< orphan*/  GPU_PERFCNT_BASE_LO ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  gpu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int panfrost_perfcnt_dump_locked(struct panfrost_device *pfdev)
{
	u64 gpuva;
	int ret;

	reinit_completion(&pfdev->perfcnt->dump_comp);
	gpuva = pfdev->perfcnt->bo->node.start << PAGE_SHIFT;
	gpu_write(pfdev, GPU_PERFCNT_BASE_LO, gpuva);
	gpu_write(pfdev, GPU_PERFCNT_BASE_HI, gpuva >> 32);
	gpu_write(pfdev, GPU_INT_CLEAR,
		  GPU_IRQ_CLEAN_CACHES_COMPLETED |
		  GPU_IRQ_PERFCNT_SAMPLE_COMPLETED);
	gpu_write(pfdev, GPU_CMD, GPU_CMD_PERFCNT_SAMPLE);
	ret = wait_for_completion_interruptible_timeout(&pfdev->perfcnt->dump_comp,
							msecs_to_jiffies(1000));
	if (!ret)
		ret = -ETIMEDOUT;
	else if (ret > 0)
		ret = 0;

	return ret;
}