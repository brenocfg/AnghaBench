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
struct camif_vp {int state; int /*<<< orphan*/  frame_sequence; int /*<<< orphan*/  active_buf_q; int /*<<< orphan*/  pending_buf_q; int /*<<< orphan*/  irq_queue; struct camif_dev* camif; } ;
struct camif_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  colorfx_cb; int /*<<< orphan*/  colorfx_cr; int /*<<< orphan*/  colorfx; TYPE_2__* variant; int /*<<< orphan*/  test_pattern; } ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {TYPE_3__ vb2_buf; scalar_t__ sequence; } ;
struct camif_buffer {unsigned int index; int /*<<< orphan*/  paddr; TYPE_1__ vb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {unsigned int ip_revision; scalar_t__ has_img_effect; } ;

/* Variables and functions */
 int CISTATUS_FRAMECNT (unsigned int) ; 
 unsigned int CISTATUS_OVF_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int S3C244X_CAMIF_IP_REV ; 
 unsigned int S3C6410_CAMIF_IP_REV ; 
 int ST_VP_ABORTING ; 
 int ST_VP_CONFIG ; 
 int ST_VP_LASTIRQ ; 
 int ST_VP_OFF ; 
 int ST_VP_PENDING ; 
 int ST_VP_RUNNING ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_active_queue_add (struct camif_vp*,struct camif_buffer*) ; 
 struct camif_buffer* camif_active_queue_peek (struct camif_vp*,unsigned int) ; 
 int /*<<< orphan*/  camif_hw_clear_fifo_overflow (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_clear_pending_irq (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_disable_capture (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_enable_scaler (struct camif_vp*,int) ; 
 unsigned int camif_hw_get_status (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_set_camera_crop (struct camif_dev*) ; 
 int /*<<< orphan*/  camif_hw_set_effect (struct camif_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_hw_set_flip (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_set_lastirq (struct camif_vp*,int) ; 
 int /*<<< orphan*/  camif_hw_set_output_addr (struct camif_vp*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  camif_hw_set_scaler (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_set_test_pattern (struct camif_dev*,int /*<<< orphan*/ ) ; 
 struct camif_buffer* camif_pending_queue_pop (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_prepare_dma_offset (struct camif_vp*) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

irqreturn_t s3c_camif_irq_handler(int irq, void *priv)
{
	struct camif_vp *vp = priv;
	struct camif_dev *camif = vp->camif;
	unsigned int ip_rev = camif->variant->ip_revision;
	unsigned int status;

	spin_lock(&camif->slock);

	if (ip_rev == S3C6410_CAMIF_IP_REV)
		camif_hw_clear_pending_irq(vp);

	status = camif_hw_get_status(vp);

	if (ip_rev == S3C244X_CAMIF_IP_REV && (status & CISTATUS_OVF_MASK)) {
		camif_hw_clear_fifo_overflow(vp);
		goto unlock;
	}

	if (vp->state & ST_VP_ABORTING) {
		if (vp->state & ST_VP_OFF) {
			/* Last IRQ */
			vp->state &= ~(ST_VP_OFF | ST_VP_ABORTING |
				       ST_VP_LASTIRQ);
			wake_up(&vp->irq_queue);
			goto unlock;
		} else if (vp->state & ST_VP_LASTIRQ) {
			camif_hw_disable_capture(vp);
			camif_hw_enable_scaler(vp, false);
			camif_hw_set_lastirq(vp, false);
			vp->state |= ST_VP_OFF;
		} else {
			/* Disable capture, enable last IRQ */
			camif_hw_set_lastirq(vp, true);
			vp->state |= ST_VP_LASTIRQ;
		}
	}

	if (!list_empty(&vp->pending_buf_q) && (vp->state & ST_VP_RUNNING) &&
	    !list_empty(&vp->active_buf_q)) {
		unsigned int index;
		struct camif_buffer *vbuf;
		/*
		 * Get previous DMA write buffer index:
		 * 0 => DMA buffer 0, 2;
		 * 1 => DMA buffer 1, 3.
		 */
		index = (CISTATUS_FRAMECNT(status) + 2) & 1;
		vbuf = camif_active_queue_peek(vp, index);

		if (!WARN_ON(vbuf == NULL)) {
			/* Dequeue a filled buffer */
			vbuf->vb.vb2_buf.timestamp = ktime_get_ns();
			vbuf->vb.sequence = vp->frame_sequence++;
			vb2_buffer_done(&vbuf->vb.vb2_buf, VB2_BUF_STATE_DONE);

			/* Set up an empty buffer at the DMA engine */
			vbuf = camif_pending_queue_pop(vp);
			vbuf->index = index;
			camif_hw_set_output_addr(vp, &vbuf->paddr, index);
			camif_hw_set_output_addr(vp, &vbuf->paddr, index + 2);

			/* Scheduled in H/W, add to the queue */
			camif_active_queue_add(vp, vbuf);
		}
	} else if (!(vp->state & ST_VP_ABORTING) &&
		   (vp->state & ST_VP_PENDING))  {
		vp->state |= ST_VP_RUNNING;
	}

	if (vp->state & ST_VP_CONFIG) {
		camif_prepare_dma_offset(vp);
		camif_hw_set_camera_crop(camif);
		camif_hw_set_scaler(vp);
		camif_hw_set_flip(vp);
		camif_hw_set_test_pattern(camif, camif->test_pattern);
		if (camif->variant->has_img_effect)
			camif_hw_set_effect(camif, camif->colorfx,
				    camif->colorfx_cr, camif->colorfx_cb);
		vp->state &= ~ST_VP_CONFIG;
	}
unlock:
	spin_unlock(&camif->slock);
	return IRQ_HANDLED;
}