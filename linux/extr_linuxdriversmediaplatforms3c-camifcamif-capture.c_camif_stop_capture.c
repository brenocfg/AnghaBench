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
struct camif_vp {int state; int /*<<< orphan*/  irq_queue; struct camif_dev* camif; } ;
struct camif_dev {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAMIF_STOP_TIMEOUT ; 
 int ST_VP_ABORTING ; 
 int ST_VP_LASTIRQ ; 
 int ST_VP_OFF ; 
 int /*<<< orphan*/  camif_hw_disable_capture (struct camif_vp*) ; 
 int /*<<< orphan*/  camif_hw_enable_scaler (struct camif_vp*,int) ; 
 int camif_reinitialize (struct camif_vp*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_vp_active (struct camif_vp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int camif_stop_capture(struct camif_vp *vp)
{
	struct camif_dev *camif = vp->camif;
	unsigned long flags;
	int ret;

	if (!s3c_vp_active(vp))
		return 0;

	spin_lock_irqsave(&camif->slock, flags);
	vp->state &= ~(ST_VP_OFF | ST_VP_LASTIRQ);
	vp->state |= ST_VP_ABORTING;
	spin_unlock_irqrestore(&camif->slock, flags);

	ret = wait_event_timeout(vp->irq_queue,
			   !(vp->state & ST_VP_ABORTING),
			   msecs_to_jiffies(CAMIF_STOP_TIMEOUT));

	spin_lock_irqsave(&camif->slock, flags);

	if (ret == 0 && !(vp->state & ST_VP_OFF)) {
		/* Timed out, forcibly stop capture */
		vp->state &= ~(ST_VP_OFF | ST_VP_ABORTING |
			       ST_VP_LASTIRQ);

		camif_hw_disable_capture(vp);
		camif_hw_enable_scaler(vp, false);
	}

	spin_unlock_irqrestore(&camif->slock, flags);

	return camif_reinitialize(vp);
}