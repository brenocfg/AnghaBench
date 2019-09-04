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
struct qxl_framebuffer {int /*<<< orphan*/  base; int /*<<< orphan*/ * obj; } ;
struct qxl_fbdev {int /*<<< orphan*/  shadow; int /*<<< orphan*/  helper; struct qxl_framebuffer qfb; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxlfb_destroy_pinned_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qxl_fbdev_destroy(struct drm_device *dev, struct qxl_fbdev *qfbdev)
{
	struct qxl_framebuffer *qfb = &qfbdev->qfb;

	drm_fb_helper_unregister_fbi(&qfbdev->helper);

	if (qfb->obj) {
		qxlfb_destroy_pinned_object(qfb->obj);
		qfb->obj = NULL;
	}
	drm_fb_helper_fini(&qfbdev->helper);
	vfree(qfbdev->shadow);
	drm_framebuffer_cleanup(&qfb->base);

	return 0;
}