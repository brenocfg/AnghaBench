#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int dummy; } ;
struct v3d_dev {int /*<<< orphan*/  job_lock; struct v3d_bin_job* bin_job; struct drm_device drm; } ;
struct TYPE_8__ {TYPE_2__* s_fence; } ;
struct TYPE_9__ {scalar_t__ irq_fence; TYPE_3__ base; struct v3d_dev* v3d; } ;
struct v3d_bin_job {int start; int end; int qma; int qms; int qts; TYPE_4__ base; } ;
struct drm_sched_job {int dummy; } ;
struct dma_fence {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  seqno; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; } ;
struct TYPE_7__ {TYPE_1__ finished; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 int /*<<< orphan*/  V3D_BIN ; 
 int /*<<< orphan*/  V3D_CLE_CT0QBA ; 
 int /*<<< orphan*/  V3D_CLE_CT0QEA ; 
 int /*<<< orphan*/  V3D_CLE_CT0QMA ; 
 int /*<<< orphan*/  V3D_CLE_CT0QMS ; 
 int /*<<< orphan*/  V3D_CLE_CT0QTS ; 
 int V3D_CLE_CT0QTS_ENABLE ; 
 int /*<<< orphan*/  V3D_CORE_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  V3D_PTB_BPOS ; 
 scalar_t__ dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct v3d_bin_job* to_bin_job (struct drm_sched_job*) ; 
 TYPE_5__* to_v3d_fence (struct dma_fence*) ; 
 int /*<<< orphan*/  trace_v3d_submit_cl (struct drm_device*,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct dma_fence* v3d_fence_create (struct v3d_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_invalidate_caches (struct v3d_dev*) ; 

__attribute__((used)) static struct dma_fence *v3d_bin_job_run(struct drm_sched_job *sched_job)
{
	struct v3d_bin_job *job = to_bin_job(sched_job);
	struct v3d_dev *v3d = job->base.v3d;
	struct drm_device *dev = &v3d->drm;
	struct dma_fence *fence;
	unsigned long irqflags;

	if (unlikely(job->base.base.s_fence->finished.error))
		return NULL;

	/* Lock required around bin_job update vs
	 * v3d_overflow_mem_work().
	 */
	spin_lock_irqsave(&v3d->job_lock, irqflags);
	v3d->bin_job = job;
	/* Clear out the overflow allocation, so we don't
	 * reuse the overflow attached to a previous job.
	 */
	V3D_CORE_WRITE(0, V3D_PTB_BPOS, 0);
	spin_unlock_irqrestore(&v3d->job_lock, irqflags);

	v3d_invalidate_caches(v3d);

	fence = v3d_fence_create(v3d, V3D_BIN);
	if (IS_ERR(fence))
		return NULL;

	if (job->base.irq_fence)
		dma_fence_put(job->base.irq_fence);
	job->base.irq_fence = dma_fence_get(fence);

	trace_v3d_submit_cl(dev, false, to_v3d_fence(fence)->seqno,
			    job->start, job->end);

	/* Set the current and end address of the control list.
	 * Writing the end register is what starts the job.
	 */
	if (job->qma) {
		V3D_CORE_WRITE(0, V3D_CLE_CT0QMA, job->qma);
		V3D_CORE_WRITE(0, V3D_CLE_CT0QMS, job->qms);
	}
	if (job->qts) {
		V3D_CORE_WRITE(0, V3D_CLE_CT0QTS,
			       V3D_CLE_CT0QTS_ENABLE |
			       job->qts);
	}
	V3D_CORE_WRITE(0, V3D_CLE_CT0QBA, job->start);
	V3D_CORE_WRITE(0, V3D_CLE_CT0QEA, job->end);

	return fence;
}