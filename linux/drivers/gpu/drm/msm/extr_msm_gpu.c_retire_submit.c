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
struct msm_ringbuffer {TYPE_1__* memptrs; } ;
struct msm_gpu_submit_stats {int alwayson_end; int alwayson_start; int cpcycles_end; int cpcycles_start; } ;
struct msm_gpu {TYPE_3__* pdev; } ;
struct msm_gem_submit {int seqno; int nr_bos; int /*<<< orphan*/  aspace; TYPE_2__* bos; } ;
struct msm_gem_object {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct msm_gem_object* obj; } ;
struct TYPE_4__ {struct msm_gpu_submit_stats* stats; } ;

/* Variables and functions */
 int MSM_GPU_SUBMIT_STATS_COUNT ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  drm_gem_object_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_move_to_inactive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_submit_free (struct msm_gem_submit*) ; 
 int /*<<< orphan*/  msm_gem_unpin_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_msm_gpu_submit_retired (struct msm_gem_submit*,int,int,int,int) ; 

__attribute__((used)) static void retire_submit(struct msm_gpu *gpu, struct msm_ringbuffer *ring,
		struct msm_gem_submit *submit)
{
	int index = submit->seqno % MSM_GPU_SUBMIT_STATS_COUNT;
	volatile struct msm_gpu_submit_stats *stats;
	u64 elapsed, clock = 0;
	int i;

	stats = &ring->memptrs->stats[index];
	/* Convert 19.2Mhz alwayson ticks to nanoseconds for elapsed time */
	elapsed = (stats->alwayson_end - stats->alwayson_start) * 10000;
	do_div(elapsed, 192);

	/* Calculate the clock frequency from the number of CP cycles */
	if (elapsed) {
		clock = (stats->cpcycles_end - stats->cpcycles_start) * 1000;
		do_div(clock, elapsed);
	}

	trace_msm_gpu_submit_retired(submit, elapsed, clock,
		stats->alwayson_start, stats->alwayson_end);

	for (i = 0; i < submit->nr_bos; i++) {
		struct msm_gem_object *msm_obj = submit->bos[i].obj;
		/* move to inactive: */
		msm_gem_move_to_inactive(&msm_obj->base);
		msm_gem_unpin_iova(&msm_obj->base, submit->aspace);
		drm_gem_object_put(&msm_obj->base);
	}

	pm_runtime_mark_last_busy(&gpu->pdev->dev);
	pm_runtime_put_autosuspend(&gpu->pdev->dev);
	msm_gem_submit_free(submit);
}