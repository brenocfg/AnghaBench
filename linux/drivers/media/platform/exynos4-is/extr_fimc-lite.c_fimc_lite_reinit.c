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
struct TYPE_2__ {int /*<<< orphan*/  vb2_buf; } ;
struct flite_buffer {TYPE_1__ vb; } ;
struct fimc_lite {int state; int /*<<< orphan*/  ve; int /*<<< orphan*/  slock; int /*<<< orphan*/  active_buf_q; int /*<<< orphan*/  pending_buf_q; } ;

/* Variables and functions */
 int ST_FLITE_OFF ; 
 int ST_FLITE_PENDING ; 
 int ST_FLITE_RUN ; 
 int ST_FLITE_STREAM ; 
 int ST_FLITE_SUSPENDED ; 
 int ST_SENSOR_STREAM ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 struct flite_buffer* fimc_lite_active_queue_pop (struct fimc_lite*) ; 
 int /*<<< orphan*/  fimc_lite_pending_queue_add (struct fimc_lite*,struct flite_buffer*) ; 
 struct flite_buffer* fimc_lite_pending_queue_pop (struct fimc_lite*) ; 
 int fimc_pipeline_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flite_hw_reset (struct fimc_lite*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_stream ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vb2_buffer_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_lite_reinit(struct fimc_lite *fimc, bool suspend)
{
	struct flite_buffer *buf;
	unsigned long flags;
	bool streaming;

	spin_lock_irqsave(&fimc->slock, flags);
	streaming = fimc->state & (1 << ST_SENSOR_STREAM);

	fimc->state &= ~(1 << ST_FLITE_RUN | 1 << ST_FLITE_OFF |
			 1 << ST_FLITE_STREAM | 1 << ST_SENSOR_STREAM);
	if (suspend)
		fimc->state |= (1 << ST_FLITE_SUSPENDED);
	else
		fimc->state &= ~(1 << ST_FLITE_PENDING |
				 1 << ST_FLITE_SUSPENDED);

	/* Release unused buffers */
	while (!suspend && !list_empty(&fimc->pending_buf_q)) {
		buf = fimc_lite_pending_queue_pop(fimc);
		vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}
	/* If suspending put unused buffers onto pending queue */
	while (!list_empty(&fimc->active_buf_q)) {
		buf = fimc_lite_active_queue_pop(fimc);
		if (suspend)
			fimc_lite_pending_queue_add(fimc, buf);
		else
			vb2_buffer_done(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	}

	spin_unlock_irqrestore(&fimc->slock, flags);

	flite_hw_reset(fimc);

	if (!streaming)
		return 0;

	return fimc_pipeline_call(&fimc->ve, set_stream, 0);
}