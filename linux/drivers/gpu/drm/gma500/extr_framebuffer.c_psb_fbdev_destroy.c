#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* obj; } ;
struct psb_framebuffer {TYPE_1__ base; } ;
struct psb_fbdev {int /*<<< orphan*/  psb_fb_helper; struct psb_framebuffer pfb; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (scalar_t__) ; 

__attribute__((used)) static int psb_fbdev_destroy(struct drm_device *dev, struct psb_fbdev *fbdev)
{
	struct psb_framebuffer *psbfb = &fbdev->pfb;

	drm_fb_helper_unregister_fbi(&fbdev->psb_fb_helper);

	drm_fb_helper_fini(&fbdev->psb_fb_helper);
	drm_framebuffer_unregister_private(&psbfb->base);
	drm_framebuffer_cleanup(&psbfb->base);

	if (psbfb->base.obj[0])
		drm_gem_object_put_unlocked(psbfb->base.obj[0]);
	return 0;
}