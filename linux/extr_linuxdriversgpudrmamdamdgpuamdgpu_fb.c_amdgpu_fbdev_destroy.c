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
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** obj; } ;
struct amdgpu_framebuffer {TYPE_1__ base; } ;
struct amdgpu_fbdev {int /*<<< orphan*/  helper; struct amdgpu_framebuffer rfb; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpufb_destroy_pinned_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (TYPE_1__*) ; 

__attribute__((used)) static int amdgpu_fbdev_destroy(struct drm_device *dev, struct amdgpu_fbdev *rfbdev)
{
	struct amdgpu_framebuffer *rfb = &rfbdev->rfb;

	drm_fb_helper_unregister_fbi(&rfbdev->helper);

	if (rfb->base.obj[0]) {
		amdgpufb_destroy_pinned_object(rfb->base.obj[0]);
		rfb->base.obj[0] = NULL;
		drm_framebuffer_unregister_private(&rfb->base);
		drm_framebuffer_cleanup(&rfb->base);
	}
	drm_fb_helper_fini(&rfbdev->helper);

	return 0;
}