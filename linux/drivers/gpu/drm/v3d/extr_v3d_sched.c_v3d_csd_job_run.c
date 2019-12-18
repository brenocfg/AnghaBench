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
struct drm_device {int dummy; } ;
struct v3d_dev {struct v3d_csd_job* csd_job; struct drm_device drm; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cfg; } ;
struct TYPE_4__ {scalar_t__ irq_fence; struct v3d_dev* v3d; } ;
struct v3d_csd_job {TYPE_2__ args; TYPE_1__ base; } ;
struct drm_sched_job {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 int /*<<< orphan*/  V3D_CORE_WRITE (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_CSD ; 
 scalar_t__ V3D_CSD_QUEUED_CFG0 ; 
 scalar_t__ dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (scalar_t__) ; 
 struct v3d_csd_job* to_csd_job (struct drm_sched_job*) ; 
 TYPE_3__* to_v3d_fence (struct dma_fence*) ; 
 int /*<<< orphan*/  trace_v3d_submit_csd (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct dma_fence* v3d_fence_create (struct v3d_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_invalidate_caches (struct v3d_dev*) ; 

__attribute__((used)) static struct dma_fence *
v3d_csd_job_run(struct drm_sched_job *sched_job)
{
	struct v3d_csd_job *job = to_csd_job(sched_job);
	struct v3d_dev *v3d = job->base.v3d;
	struct drm_device *dev = &v3d->drm;
	struct dma_fence *fence;
	int i;

	v3d->csd_job = job;

	v3d_invalidate_caches(v3d);

	fence = v3d_fence_create(v3d, V3D_CSD);
	if (IS_ERR(fence))
		return NULL;

	if (job->base.irq_fence)
		dma_fence_put(job->base.irq_fence);
	job->base.irq_fence = dma_fence_get(fence);

	trace_v3d_submit_csd(dev, to_v3d_fence(fence)->seqno);

	for (i = 1; i <= 6; i++)
		V3D_CORE_WRITE(0, V3D_CSD_QUEUED_CFG0 + 4 * i, job->args.cfg[i]);
	/* CFG0 write kicks off the job. */
	V3D_CORE_WRITE(0, V3D_CSD_QUEUED_CFG0, job->args.cfg[0]);

	return fence;
}