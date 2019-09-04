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
struct TYPE_4__ {int field; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct vpfe_device {scalar_t__ cur_frm; scalar_t__ next_frm; int field; int /*<<< orphan*/  ccdc; int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; TYPE_3__ fmt; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int V4L2_FIELD_NONE ; 
 int V4L2_FIELD_SEQ_TB ; 
 int /*<<< orphan*/  VPFE_IRQ_STS ; 
 int VPFE_VDINT0 ; 
 int VPFE_VDINT1 ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vpfe_ccdc_getfid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_clear_intr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vpfe_process_buffer_complete (struct vpfe_device*) ; 
 int vpfe_reg_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_schedule_bottom_field (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_schedule_next_buffer (struct vpfe_device*) ; 

__attribute__((used)) static irqreturn_t vpfe_isr(int irq, void *dev)
{
	struct vpfe_device *vpfe = (struct vpfe_device *)dev;
	enum v4l2_field field;
	int intr_status;
	int fid;

	intr_status = vpfe_reg_read(&vpfe->ccdc, VPFE_IRQ_STS);

	if (intr_status & VPFE_VDINT0) {
		field = vpfe->fmt.fmt.pix.field;

		if (field == V4L2_FIELD_NONE) {
			/* handle progressive frame capture */
			if (vpfe->cur_frm != vpfe->next_frm)
				vpfe_process_buffer_complete(vpfe);
			goto next_intr;
		}

		/* interlaced or TB capture check which field
		   we are in hardware */
		fid = vpfe_ccdc_getfid(&vpfe->ccdc);

		/* switch the software maintained field id */
		vpfe->field ^= 1;
		if (fid == vpfe->field) {
			/* we are in-sync here,continue */
			if (fid == 0) {
				/*
				 * One frame is just being captured. If the
				 * next frame is available, release the
				 * current frame and move on
				 */
				if (vpfe->cur_frm != vpfe->next_frm)
					vpfe_process_buffer_complete(vpfe);
				/*
				 * based on whether the two fields are stored
				 * interleave or separately in memory,
				 * reconfigure the CCDC memory address
				 */
				if (field == V4L2_FIELD_SEQ_TB)
					vpfe_schedule_bottom_field(vpfe);

				goto next_intr;
			}
			/*
			 * if one field is just being captured configure
			 * the next frame get the next frame from the empty
			 * queue if no frame is available hold on to the
			 * current buffer
			 */
			spin_lock(&vpfe->dma_queue_lock);
			if (!list_empty(&vpfe->dma_queue) &&
			    vpfe->cur_frm == vpfe->next_frm)
				vpfe_schedule_next_buffer(vpfe);
			spin_unlock(&vpfe->dma_queue_lock);
		} else if (fid == 0) {
			/*
			 * out of sync. Recover from any hardware out-of-sync.
			 * May loose one frame
			 */
			vpfe->field = fid;
		}
	}

next_intr:
	if (intr_status & VPFE_VDINT1) {
		spin_lock(&vpfe->dma_queue_lock);
		if (vpfe->fmt.fmt.pix.field == V4L2_FIELD_NONE &&
		    !list_empty(&vpfe->dma_queue) &&
		    vpfe->cur_frm == vpfe->next_frm)
			vpfe_schedule_next_buffer(vpfe);
		spin_unlock(&vpfe->dma_queue_lock);
	}

	vpfe_clear_intr(&vpfe->ccdc, intr_status);

	return IRQ_HANDLED;
}