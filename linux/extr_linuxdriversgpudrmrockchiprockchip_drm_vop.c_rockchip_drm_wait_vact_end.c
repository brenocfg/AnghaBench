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
struct vop {int /*<<< orphan*/  vop_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  line_flag_completion; int /*<<< orphan*/  is_enabled; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct vop* to_vop (struct drm_crtc*) ; 
 int /*<<< orphan*/  vop_line_flag_irq_disable (struct vop*) ; 
 int /*<<< orphan*/  vop_line_flag_irq_enable (struct vop*) ; 
 scalar_t__ vop_line_flag_irq_is_enabled (struct vop*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rockchip_drm_wait_vact_end(struct drm_crtc *crtc, unsigned int mstimeout)
{
	struct vop *vop = to_vop(crtc);
	unsigned long jiffies_left;
	int ret = 0;

	if (!crtc || !vop->is_enabled)
		return -ENODEV;

	mutex_lock(&vop->vop_lock);
	if (mstimeout <= 0) {
		ret = -EINVAL;
		goto out;
	}

	if (vop_line_flag_irq_is_enabled(vop)) {
		ret = -EBUSY;
		goto out;
	}

	reinit_completion(&vop->line_flag_completion);
	vop_line_flag_irq_enable(vop);

	jiffies_left = wait_for_completion_timeout(&vop->line_flag_completion,
						   msecs_to_jiffies(mstimeout));
	vop_line_flag_irq_disable(vop);

	if (jiffies_left == 0) {
		DRM_DEV_ERROR(vop->dev, "Timeout waiting for IRQ\n");
		ret = -ETIMEDOUT;
		goto out;
	}

out:
	mutex_unlock(&vop->vop_lock);
	return ret;
}