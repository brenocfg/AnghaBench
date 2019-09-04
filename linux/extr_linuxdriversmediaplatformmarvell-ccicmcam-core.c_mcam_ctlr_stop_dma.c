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
struct mcam_camera {int /*<<< orphan*/  dev_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_DMA_ACTIVE ; 
 int /*<<< orphan*/  CF_SG_RESTART ; 
 int /*<<< orphan*/  S_IDLE ; 
 int /*<<< orphan*/  cam_err (struct mcam_camera*,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcam_ctlr_irq_disable (struct mcam_camera*) ; 
 int /*<<< orphan*/  mcam_ctlr_stop (struct mcam_camera*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcam_ctlr_stop_dma(struct mcam_camera *cam)
{
	unsigned long flags;

	/*
	 * Theory: stop the camera controller (whether it is operating
	 * or not).  Delay briefly just in case we race with the SOF
	 * interrupt, then wait until no DMA is active.
	 */
	spin_lock_irqsave(&cam->dev_lock, flags);
	clear_bit(CF_SG_RESTART, &cam->flags);
	mcam_ctlr_stop(cam);
	cam->state = S_IDLE;
	spin_unlock_irqrestore(&cam->dev_lock, flags);
	/*
	 * This is a brutally long sleep, but experience shows that
	 * it can take the controller a while to get the message that
	 * it needs to stop grabbing frames.  In particular, we can
	 * sometimes (on mmp) get a frame at the end WITHOUT the
	 * start-of-frame indication.
	 */
	msleep(150);
	if (test_bit(CF_DMA_ACTIVE, &cam->flags))
		cam_err(cam, "Timeout waiting for DMA to end\n");
		/* This would be bad news - what now? */
	spin_lock_irqsave(&cam->dev_lock, flags);
	mcam_ctlr_irq_disable(cam);
	spin_unlock_irqrestore(&cam->dev_lock, flags);
}