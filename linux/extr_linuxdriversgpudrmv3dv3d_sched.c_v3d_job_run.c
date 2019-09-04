#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* s_fence; } ;
struct v3d_job {int start; int end; scalar_t__ done_fence; struct v3d_exec_info* exec; TYPE_3__ base; } ;
struct v3d_exec_info {int qma; int qms; int qts; struct v3d_dev* v3d; struct v3d_job bin; } ;
struct drm_device {int dummy; } ;
struct v3d_dev {int /*<<< orphan*/  job_lock; struct v3d_exec_info* render_job; struct v3d_exec_info* bin_job; struct drm_device drm; } ;
struct drm_sched_job {int dummy; } ;
struct dma_fence {int dummy; } ;
typedef  enum v3d_queue { ____Placeholder_v3d_queue } v3d_queue ;
struct TYPE_8__ {int /*<<< orphan*/  seqno; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
struct TYPE_6__ {TYPE_1__ finished; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 int V3D_BIN ; 
 int /*<<< orphan*/  V3D_CLE_CT0QMA ; 
 int /*<<< orphan*/  V3D_CLE_CT0QMS ; 
 int /*<<< orphan*/  V3D_CLE_CT0QTS ; 
 int V3D_CLE_CT0QTS_ENABLE ; 
 int /*<<< orphan*/  V3D_CLE_CTNQBA (int) ; 
 int /*<<< orphan*/  V3D_CLE_CTNQEA (int) ; 
 int /*<<< orphan*/  V3D_CORE_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  V3D_PTB_BPOS ; 
 int V3D_RENDER ; 
 scalar_t__ dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_4__* to_v3d_fence (struct dma_fence*) ; 
 struct v3d_job* to_v3d_job (struct drm_sched_job*) ; 
 int /*<<< orphan*/  trace_v3d_submit_cl (struct drm_device*,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct dma_fence* v3d_fence_create (struct v3d_dev*,int) ; 
 int /*<<< orphan*/  v3d_invalidate_caches (struct v3d_dev*) ; 

__attribute__((used)) static struct dma_fence *v3d_job_run(struct drm_sched_job *sched_job)
{
	struct v3d_job *job = to_v3d_job(sched_job);
	struct v3d_exec_info *exec = job->exec;
	enum v3d_queue q = job == &exec->bin ? V3D_BIN : V3D_RENDER;
	struct v3d_dev *v3d = exec->v3d;
	struct drm_device *dev = &v3d->drm;
	struct dma_fence *fence;
	unsigned long irqflags;

	if (unlikely(job->base.s_fence->finished.error))
		return NULL;

	/* Lock required around bin_job update vs
	 * v3d_overflow_mem_work().
	 */
	spin_lock_irqsave(&v3d->job_lock, irqflags);
	if (q == V3D_BIN) {
		v3d->bin_job = job->exec;

		/* Clear out the overflow allocation, so we don't
		 * reuse the overflow attached to a previous job.
		 */
		V3D_CORE_WRITE(0, V3D_PTB_BPOS, 0);
	} else {
		v3d->render_job = job->exec;
	}
	spin_unlock_irqrestore(&v3d->job_lock, irqflags);

	/* Can we avoid this flush when q==RENDER?  We need to be
	 * careful of scheduling, though -- imagine job0 rendering to
	 * texture and job1 reading, and them being executed as bin0,
	 * bin1, render0, render1, so that render1's flush at bin time
	 * wasn't enough.
	 */
	v3d_invalidate_caches(v3d);

	fence = v3d_fence_create(v3d, q);
	if (IS_ERR(fence))
		return NULL;

	if (job->done_fence)
		dma_fence_put(job->done_fence);
	job->done_fence = dma_fence_get(fence);

	trace_v3d_submit_cl(dev, q == V3D_RENDER, to_v3d_fence(fence)->seqno,
			    job->start, job->end);

	if (q == V3D_BIN) {
		if (exec->qma) {
			V3D_CORE_WRITE(0, V3D_CLE_CT0QMA, exec->qma);
			V3D_CORE_WRITE(0, V3D_CLE_CT0QMS, exec->qms);
		}
		if (exec->qts) {
			V3D_CORE_WRITE(0, V3D_CLE_CT0QTS,
				       V3D_CLE_CT0QTS_ENABLE |
				       exec->qts);
		}
	} else {
		/* XXX: Set the QCFG */
	}

	/* Set the current and end address of the control list.
	 * Writing the end register is what starts the job.
	 */
	V3D_CORE_WRITE(0, V3D_CLE_CTNQBA(q), job->start);
	V3D_CORE_WRITE(0, V3D_CLE_CTNQEA(q), job->end);

	return fence;
}