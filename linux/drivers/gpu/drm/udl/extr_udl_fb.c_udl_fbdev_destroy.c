#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* obj; int /*<<< orphan*/  base; } ;
struct udl_fbdev {TYPE_2__ ufb; int /*<<< orphan*/  helper; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udl_fbdev_destroy(struct drm_device *dev,
			      struct udl_fbdev *ufbdev)
{
	drm_fb_helper_unregister_fbi(&ufbdev->helper);
	drm_fb_helper_fini(&ufbdev->helper);
	if (ufbdev->ufb.obj) {
		drm_framebuffer_unregister_private(&ufbdev->ufb.base);
		drm_framebuffer_cleanup(&ufbdev->ufb.base);
		drm_gem_object_put_unlocked(&ufbdev->ufb.obj->base);
	}
}