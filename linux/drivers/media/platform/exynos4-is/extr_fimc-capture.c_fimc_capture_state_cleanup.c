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
struct fimc_vid_cap {int /*<<< orphan*/  ve; scalar_t__ buf_index; int /*<<< orphan*/  active_buf_q; int /*<<< orphan*/  pending_buf_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; } ;
struct fimc_vid_buffer {TYPE_1__ vb; } ;
struct fimc_dev {int state; int /*<<< orphan*/  slock; struct fimc_vid_cap vid_cap; } ;

/* Variables and functions */
 int ST_CAPT_ISP_STREAM ; 
 int ST_CAPT_PEND ; 
 int ST_CAPT_RUN ; 
 int ST_CAPT_SHUT ; 
 int ST_CAPT_STREAM ; 
 int ST_CAPT_SUSPENDED ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 struct fimc_vid_buffer* fimc_active_queue_pop (struct fimc_vid_cap*) ; 
 int /*<<< orphan*/  fimc_hw_reset (struct fimc_dev*) ; 
 int /*<<< orphan*/  fimc_pending_queue_add (struct fimc_vid_cap*,struct fimc_vid_buffer*) ; 
 struct fimc_vid_buffer* fimc_pending_queue_pop (struct fimc_vid_cap*) ; 
 int fimc_pipeline_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_stream ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_capture_state_cleanup(struct fimc_dev *fimc, bool suspend)
{
	struct fimc_vid_cap *cap = &fimc->vid_cap;
	struct fimc_vid_buffer *buf;
	unsigned long flags;
	bool streaming;

	spin_lock_irqsave(&fimc->slock, flags);
	streaming = fimc->state & (1 << ST_CAPT_ISP_STREAM);

	fimc->state &= ~(1 << ST_CAPT_RUN | 1 << ST_CAPT_SHUT |
			 1 << ST_CAPT_STREAM | 1 << ST_CAPT_ISP_STREAM);
	if (suspend)
		fimc->state |= (1 << ST_CAPT_SUSPENDED);
	else
		fimc->state &= ~(1 << ST_CAPT_PEND | 1 << ST_CAPT_SUSPENDED);

	/* Release unused buffers */
	while (!suspend && !list_empty(&cap->pending_buf_q)) {
		buf = fimc_pending_queue_pop(cap);
		vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}
	/* If suspending put unused buffers onto pending queue */
	while (!list_empty(&cap->active_buf_q)) {
		buf = fimc_active_queue_pop(cap);
		if (suspend)
			fimc_pending_queue_add(cap, buf);
		else
			vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}

	fimc_hw_reset(fimc);
	cap->buf_index = 0;

	spin_unlock_irqrestore(&fimc->slock, flags);

	if (streaming)
		return fimc_pipeline_call(&cap->ve, set_stream, 0);
	else
		return 0;
}