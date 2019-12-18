#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mcam_camera {unsigned int nbufs; scalar_t__ buffer_mode; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ B_DMA_sg ; 
 scalar_t__ CF_DMA_ACTIVE ; 
 scalar_t__ CF_FRAME_SOF0 ; 
 int /*<<< orphan*/  FRAMEIRQS ; 
 unsigned int IRQ_EOF0 ; 
 unsigned int IRQ_HANDLED ; 
 unsigned int IRQ_SOF0 ; 
 int /*<<< orphan*/  REG_IRQSTAT ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcam_ctlr_stop (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_frame_complete (struct mcam_camera*,unsigned int) ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ *) ; 

int mccic_irq(struct mcam_camera *cam, unsigned int irqs)
{
	unsigned int frame, handled = 0;

	mcam_reg_write(cam, REG_IRQSTAT, FRAMEIRQS); /* Clear'em all */
	/*
	 * Handle any frame completions.  There really should
	 * not be more than one of these, or we have fallen
	 * far behind.
	 *
	 * When running in S/G mode, the frame number lacks any
	 * real meaning - there's only one descriptor array - but
	 * the controller still picks a different one to signal
	 * each time.
	 */
	for (frame = 0; frame < cam->nbufs; frame++)
		if (irqs & (IRQ_EOF0 << frame) &&
			test_bit(CF_FRAME_SOF0 + frame, &cam->flags)) {
			mcam_frame_complete(cam, frame);
			handled = 1;
			clear_bit(CF_FRAME_SOF0 + frame, &cam->flags);
			if (cam->buffer_mode == B_DMA_sg)
				break;
		}
	/*
	 * If a frame starts, note that we have DMA active.  This
	 * code assumes that we won't get multiple frame interrupts
	 * at once; may want to rethink that.
	 */
	for (frame = 0; frame < cam->nbufs; frame++) {
		if (irqs & (IRQ_SOF0 << frame)) {
			set_bit(CF_FRAME_SOF0 + frame, &cam->flags);
			handled = IRQ_HANDLED;
		}
	}

	if (handled == IRQ_HANDLED) {
		set_bit(CF_DMA_ACTIVE, &cam->flags);
		if (cam->buffer_mode == B_DMA_sg)
			mcam_ctlr_stop(cam);
	}
	return handled;
}