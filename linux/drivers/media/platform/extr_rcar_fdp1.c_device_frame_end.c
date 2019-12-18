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
struct fdp1_job {TYPE_1__* dst; int /*<<< orphan*/  active; int /*<<< orphan*/  previous; } ;
struct fdp1_dev {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct fdp1_ctx {scalar_t__ num_processed; scalar_t__ translen; TYPE_2__ fh; struct fdp1_dev* fdp1; scalar_t__ aborting; int /*<<< orphan*/  deint_mode; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;
struct TYPE_3__ {int /*<<< orphan*/  vb; } ;

/* Variables and functions */
 scalar_t__ FDP1_DEINT_MODE_USES_PREV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (struct fdp1_dev*,char*,...) ; 
 int /*<<< orphan*/  fdp1_device_process (struct fdp1_ctx*) ; 
 int /*<<< orphan*/  fdp1_field_complete (struct fdp1_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdp1_job_free (struct fdp1_dev*,struct fdp1_job*) ; 
 struct fdp1_job* get_hw_queued_job (struct fdp1_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (int /*<<< orphan*/ ,int) ; 
 struct fdp1_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_frame_end(struct fdp1_dev *fdp1,
			     enum vb2_buffer_state state)
{
	struct fdp1_ctx *ctx;
	unsigned long flags;
	struct fdp1_job *job = get_hw_queued_job(fdp1);

	dprintk(fdp1, "+\n");

	ctx = v4l2_m2m_get_curr_priv(fdp1->m2m_dev);

	if (ctx == NULL) {
		v4l2_err(&fdp1->v4l2_dev,
			"Instance released before the end of transaction\n");
		return;
	}

	ctx->num_processed++;

	/*
	 * fdp1_field_complete will call buf_done only when the last vb2_buffer
	 * reference is complete
	 */
	if (FDP1_DEINT_MODE_USES_PREV(ctx->deint_mode))
		fdp1_field_complete(ctx, job->previous);
	else
		fdp1_field_complete(ctx, job->active);

	spin_lock_irqsave(&fdp1->irqlock, flags);
	v4l2_m2m_buf_done(job->dst->vb, state);
	job->dst = NULL;
	spin_unlock_irqrestore(&fdp1->irqlock, flags);

	/* Move this job back to the free job list */
	fdp1_job_free(fdp1, job);

	dprintk(fdp1, "curr_ctx->num_processed %d curr_ctx->translen %d\n",
		ctx->num_processed, ctx->translen);

	if (ctx->num_processed == ctx->translen ||
			ctx->aborting) {
		dprintk(ctx->fdp1, "Finishing transaction\n");
		ctx->num_processed = 0;
		v4l2_m2m_job_finish(fdp1->m2m_dev, ctx->fh.m2m_ctx);
	} else {
		/*
		 * For pipelined performance support, this would
		 * be called from a VINT handler
		 */
		fdp1_device_process(ctx);
	}
}