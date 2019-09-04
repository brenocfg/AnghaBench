#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int dummy; } ;
struct fdp1_job {TYPE_7__* active; TYPE_5__* dst; int /*<<< orphan*/  next; TYPE_7__* previous; } ;
struct fdp1_dev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  m2m_ctx; } ;
struct fdp1_ctx {unsigned int buffers_queued; int /*<<< orphan*/  translen; int /*<<< orphan*/  deint_mode; TYPE_7__* previous; int /*<<< orphan*/  sequence; TYPE_1__ fh; struct fdp1_dev* fdp1; } ;
struct fdp1_buffer {TYPE_5__* fields; } ;
struct TYPE_14__ {TYPE_6__* vb; } ;
struct TYPE_10__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_13__ {int flags; TYPE_3__ vb2_buf; int /*<<< orphan*/  sequence; } ;
struct TYPE_12__ {TYPE_4__* vb; } ;
struct TYPE_9__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_11__ {int flags; TYPE_2__ vb2_buf; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 scalar_t__ FDP1_DEINT_MODE_USES_NEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ FDP1_DEINT_MODE_USES_PREV (int /*<<< orphan*/ ) ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 int /*<<< orphan*/  dprintk (struct fdp1_dev*,char*,...) ; 
 TYPE_7__* fdp1_dequeue_field (struct fdp1_ctx*) ; 
 struct fdp1_job* fdp1_job_alloc (struct fdp1_dev*) ; 
 int /*<<< orphan*/  fdp1_job_free (struct fdp1_dev*,struct fdp1_job*) ; 
 int /*<<< orphan*/  fdp1_peek_queued_field (struct fdp1_ctx*) ; 
 int /*<<< orphan*/  queue_job (struct fdp1_dev*,struct fdp1_job*) ; 
 struct fdp1_buffer* to_fdp1_buffer (struct vb2_v4l2_buffer*) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fdp1_job *fdp1_prepare_job(struct fdp1_ctx *ctx)
{
	struct vb2_v4l2_buffer *vbuf;
	struct fdp1_buffer *fbuf;
	struct fdp1_dev *fdp1 = ctx->fdp1;
	struct fdp1_job *job;
	unsigned int buffers_required = 1;

	dprintk(fdp1, "+\n");

	if (FDP1_DEINT_MODE_USES_NEXT(ctx->deint_mode))
		buffers_required = 2;

	if (ctx->buffers_queued < buffers_required)
		return NULL;

	job = fdp1_job_alloc(fdp1);
	if (!job) {
		dprintk(fdp1, "No free jobs currently available\n");
		return NULL;
	}

	job->active = fdp1_dequeue_field(ctx);
	if (!job->active) {
		/* Buffer check should prevent this ever happening */
		dprintk(fdp1, "No input buffers currently available\n");

		fdp1_job_free(fdp1, job);
		return NULL;
	}

	dprintk(fdp1, "+ Buffer en-route...\n");

	/* Source buffers have been prepared on our buffer_queue
	 * Prepare our Output buffer
	 */
	vbuf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
	fbuf = to_fdp1_buffer(vbuf);
	job->dst = &fbuf->fields[0];

	job->active->vb->sequence = ctx->sequence;
	job->dst->vb->sequence = ctx->sequence;
	ctx->sequence++;

	if (FDP1_DEINT_MODE_USES_PREV(ctx->deint_mode)) {
		job->previous = ctx->previous;

		/* Active buffer becomes the next job's previous buffer */
		ctx->previous = job->active;
	}

	if (FDP1_DEINT_MODE_USES_NEXT(ctx->deint_mode)) {
		/* Must be called after 'active' is dequeued */
		job->next = fdp1_peek_queued_field(ctx);
	}

	/* Transfer timestamps and flags from src->dst */

	job->dst->vb->vb2_buf.timestamp = job->active->vb->vb2_buf.timestamp;

	job->dst->vb->flags = job->active->vb->flags &
				V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

	/* Ideally, the frame-end function will just 'check' to see
	 * if there are more jobs instead
	 */
	ctx->translen++;

	/* Finally, Put this job on the processing queue */
	queue_job(fdp1, job);

	dprintk(fdp1, "Job Queued translen = %d\n", ctx->translen);

	return job;
}