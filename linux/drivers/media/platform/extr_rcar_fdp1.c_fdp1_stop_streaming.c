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
struct vb2_v4l2_buffer {int dummy; } ;
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct fdp1_job {TYPE_2__* dst; struct fdp1_field_buffer* active; struct fdp1_field_buffer* previous; } ;
struct fdp1_field_buffer {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct fdp1_ctx {TYPE_3__* fdp1; struct fdp1_field_buffer* previous; int /*<<< orphan*/  deint_mode; int /*<<< orphan*/  fields_queue; int /*<<< orphan*/ * smsk_cpu; scalar_t__* smsk_addr; int /*<<< orphan*/  smsk_size; TYPE_1__ fh; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_job_list; int /*<<< orphan*/  queued_job_list; int /*<<< orphan*/  dev; int /*<<< orphan*/  irqlock; } ;
struct TYPE_5__ {struct vb2_v4l2_buffer* vb; } ;

/* Variables and functions */
 scalar_t__ FDP1_DEINT_MODE_USES_PREV (int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct fdp1_field_buffer* fdp1_dequeue_field (struct fdp1_ctx*) ; 
 int /*<<< orphan*/  fdp1_field_complete (struct fdp1_ctx*,struct fdp1_field_buffer*) ; 
 struct fdp1_job* get_queued_job (TYPE_3__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 struct fdp1_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void fdp1_stop_streaming(struct vb2_queue *q)
{
	struct fdp1_ctx *ctx = vb2_get_drv_priv(q);
	struct vb2_v4l2_buffer *vbuf;
	unsigned long flags;

	while (1) {
		if (V4L2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
		else
			vbuf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);
		if (vbuf == NULL)
			break;
		spin_lock_irqsave(&ctx->fdp1->irqlock, flags);
		v4l2_m2m_buf_done(vbuf, VB2_BUF_STATE_ERROR);
		spin_unlock_irqrestore(&ctx->fdp1->irqlock, flags);
	}

	/* Empty Output queues */
	if (V4L2_TYPE_IS_OUTPUT(q->type)) {
		/* Empty our internal queues */
		struct fdp1_field_buffer *fbuf;

		/* Free any queued buffers */
		fbuf = fdp1_dequeue_field(ctx);
		while (fbuf != NULL) {
			fdp1_field_complete(ctx, fbuf);
			fbuf = fdp1_dequeue_field(ctx);
		}

		/* Free smsk_data */
		if (ctx->smsk_cpu) {
			dma_free_coherent(ctx->fdp1->dev, ctx->smsk_size,
					  ctx->smsk_cpu, ctx->smsk_addr[0]);
			ctx->smsk_addr[0] = ctx->smsk_addr[1] = 0;
			ctx->smsk_cpu = NULL;
		}

		WARN(!list_empty(&ctx->fields_queue),
		     "Buffer queue not empty");
	} else {
		/* Empty Capture queues (Jobs) */
		struct fdp1_job *job;

		job = get_queued_job(ctx->fdp1);
		while (job) {
			if (FDP1_DEINT_MODE_USES_PREV(ctx->deint_mode))
				fdp1_field_complete(ctx, job->previous);
			else
				fdp1_field_complete(ctx, job->active);

			v4l2_m2m_buf_done(job->dst->vb, VB2_BUF_STATE_ERROR);
			job->dst = NULL;

			job = get_queued_job(ctx->fdp1);
		}

		/* Free any held buffer in the ctx */
		fdp1_field_complete(ctx, ctx->previous);

		WARN(!list_empty(&ctx->fdp1->queued_job_list),
		     "Queued Job List not empty");

		WARN(!list_empty(&ctx->fdp1->hw_job_list),
		     "HW Job list not empty");
	}
}