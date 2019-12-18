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
struct mxsfb_drm_private {int /*<<< orphan*/  pipe; } ;
struct drm_device {struct mxsfb_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxsfb_pipe_disable_vblank (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mxsfb_irq_preinstall(struct drm_device *drm)
{
	struct mxsfb_drm_private *mxsfb = drm->dev_private;

	mxsfb_pipe_disable_vblank(&mxsfb->pipe);
}