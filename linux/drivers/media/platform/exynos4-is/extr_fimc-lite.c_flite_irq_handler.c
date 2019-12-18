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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_5__ {TYPE_3__ vb2_buf; scalar_t__ sequence; } ;
struct flite_buffer {TYPE_2__ vb; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_overflow; } ;
struct fimc_lite {int /*<<< orphan*/  slock; int /*<<< orphan*/  state; int /*<<< orphan*/  pending_buf_q; int /*<<< orphan*/  frame_count; int /*<<< orphan*/  active_buf_q; int /*<<< orphan*/  out_path; int /*<<< orphan*/  irq_queue; TYPE_1__ events; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ FIMC_IO_DMA ; 
 int FLITE_REG_CISTATUS_IRQ_SRC_FRMEND ; 
 int FLITE_REG_CISTATUS_IRQ_SRC_FRMSTART ; 
 int FLITE_REG_CISTATUS_IRQ_SRC_LASTCAPEND ; 
 int FLITE_REG_CISTATUS_IRQ_SRC_OVERFLOW ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ST_FLITE_CONFIG ; 
 int /*<<< orphan*/  ST_FLITE_OFF ; 
 int /*<<< orphan*/  ST_FLITE_RUN ; 
 int /*<<< orphan*/  ST_FLITE_STREAM ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimc_lite_active_queue_add (struct fimc_lite*,struct flite_buffer*) ; 
 struct flite_buffer* fimc_lite_active_queue_pop (struct fimc_lite*) ; 
 int /*<<< orphan*/  fimc_lite_config_update (struct fimc_lite*) ; 
 struct flite_buffer* fimc_lite_pending_queue_pop (struct fimc_lite*) ; 
 int /*<<< orphan*/  flite_hw_capture_stop (struct fimc_lite*) ; 
 int /*<<< orphan*/  flite_hw_clear_last_capture_end (struct fimc_lite*) ; 
 int /*<<< orphan*/  flite_hw_clear_pending_irq (struct fimc_lite*) ; 
 int flite_hw_get_interrupt_source (struct fimc_lite*) ; 
 int /*<<< orphan*/  flite_hw_mask_dma_buffer (struct fimc_lite*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flite_hw_set_dma_buffer (struct fimc_lite*,struct flite_buffer*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t flite_irq_handler(int irq, void *priv)
{
	struct fimc_lite *fimc = priv;
	struct flite_buffer *vbuf;
	unsigned long flags;
	u32 intsrc;

	spin_lock_irqsave(&fimc->slock, flags);

	intsrc = flite_hw_get_interrupt_source(fimc);
	flite_hw_clear_pending_irq(fimc);

	if (test_and_clear_bit(ST_FLITE_OFF, &fimc->state)) {
		wake_up(&fimc->irq_queue);
		goto done;
	}

	if (intsrc & FLITE_REG_CISTATUS_IRQ_SRC_OVERFLOW) {
		clear_bit(ST_FLITE_RUN, &fimc->state);
		fimc->events.data_overflow++;
	}

	if (intsrc & FLITE_REG_CISTATUS_IRQ_SRC_LASTCAPEND) {
		flite_hw_clear_last_capture_end(fimc);
		clear_bit(ST_FLITE_STREAM, &fimc->state);
		wake_up(&fimc->irq_queue);
	}

	if (atomic_read(&fimc->out_path) != FIMC_IO_DMA)
		goto done;

	if ((intsrc & FLITE_REG_CISTATUS_IRQ_SRC_FRMSTART) &&
	    test_bit(ST_FLITE_RUN, &fimc->state) &&
	    !list_empty(&fimc->pending_buf_q)) {
		vbuf = fimc_lite_pending_queue_pop(fimc);
		flite_hw_set_dma_buffer(fimc, vbuf);
		fimc_lite_active_queue_add(fimc, vbuf);
	}

	if ((intsrc & FLITE_REG_CISTATUS_IRQ_SRC_FRMEND) &&
	    test_bit(ST_FLITE_RUN, &fimc->state) &&
	    !list_empty(&fimc->active_buf_q)) {
		vbuf = fimc_lite_active_queue_pop(fimc);
		vbuf->vb.vb2_buf.timestamp = ktime_get_ns();
		vbuf->vb.sequence = fimc->frame_count++;
		flite_hw_mask_dma_buffer(fimc, vbuf->index);
		vb2_buffer_done(&vbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	}

	if (test_bit(ST_FLITE_CONFIG, &fimc->state))
		fimc_lite_config_update(fimc);

	if (list_empty(&fimc->pending_buf_q)) {
		flite_hw_capture_stop(fimc);
		clear_bit(ST_FLITE_STREAM, &fimc->state);
	}
done:
	set_bit(ST_FLITE_RUN, &fimc->state);
	spin_unlock_irqrestore(&fimc->slock, flags);
	return IRQ_HANDLED;
}