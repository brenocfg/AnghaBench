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
typedef  int u32 ;
struct rcar_du_device {TYPE_1__* info; } ;
struct rcar_du_crtc {scalar_t__ vblank_count; int /*<<< orphan*/  crtc; int /*<<< orphan*/  vblank_lock; int /*<<< orphan*/  vblank_wait; struct rcar_du_device* dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSRCR ; 
 int DSRCR_MASK ; 
 int /*<<< orphan*/  DSSR ; 
 int DSSR_VBK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcar_du_crtc_finish_page_flip (struct rcar_du_crtc*) ; 
 int rcar_du_crtc_read (struct rcar_du_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_crtc_write (struct rcar_du_crtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rcar_du_crtc_irq(int irq, void *arg)
{
	struct rcar_du_crtc *rcrtc = arg;
	struct rcar_du_device *rcdu = rcrtc->dev;
	irqreturn_t ret = IRQ_NONE;
	u32 status;

	spin_lock(&rcrtc->vblank_lock);

	status = rcar_du_crtc_read(rcrtc, DSSR);
	rcar_du_crtc_write(rcrtc, DSRCR, status & DSRCR_MASK);

	if (status & DSSR_VBK) {
		/*
		 * Wake up the vblank wait if the counter reaches 0. This must
		 * be protected by the vblank_lock to avoid races in
		 * rcar_du_crtc_disable_planes().
		 */
		if (rcrtc->vblank_count) {
			if (--rcrtc->vblank_count == 0)
				wake_up(&rcrtc->vblank_wait);
		}
	}

	spin_unlock(&rcrtc->vblank_lock);

	if (status & DSSR_VBK) {
		if (rcdu->info->gen < 3) {
			drm_crtc_handle_vblank(&rcrtc->crtc);
			rcar_du_crtc_finish_page_flip(rcrtc);
		}

		ret = IRQ_HANDLED;
	}

	return ret;
}