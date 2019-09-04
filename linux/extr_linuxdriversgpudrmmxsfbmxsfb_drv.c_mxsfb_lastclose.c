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
struct mxsfb_drm_private {int /*<<< orphan*/  fbdev; } ;
struct drm_device {struct mxsfb_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fbdev_cma_restore_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxsfb_lastclose(struct drm_device *drm)
{
	struct mxsfb_drm_private *mxsfb = drm->dev_private;

	drm_fbdev_cma_restore_mode(mxsfb->fbdev);
}