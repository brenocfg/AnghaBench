#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* fbdev; } ;
struct vbox_framebuffer {int /*<<< orphan*/  base; int /*<<< orphan*/ * obj; } ;
struct vbox_private {TYPE_2__ fb_helper; struct vbox_framebuffer afb; } ;
struct drm_gem_vram_object {int dummy; } ;
struct TYPE_4__ {scalar_t__ fbdefio; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_framebuffer_unregister_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_vram_kunmap (struct drm_gem_vram_object*) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (struct drm_gem_vram_object*) ; 
 int /*<<< orphan*/  fb_deferred_io_cleanup (TYPE_1__*) ; 

void vbox_fbdev_fini(struct vbox_private *vbox)
{
	struct vbox_framebuffer *afb = &vbox->afb;

#ifdef CONFIG_DRM_KMS_FB_HELPER
	if (vbox->fb_helper.fbdev && vbox->fb_helper.fbdev->fbdefio)
		fb_deferred_io_cleanup(vbox->fb_helper.fbdev);
#endif

	drm_fb_helper_unregister_fbi(&vbox->fb_helper);

	if (afb->obj) {
		struct drm_gem_vram_object *gbo = drm_gem_vram_of_gem(afb->obj);

		drm_gem_vram_kunmap(gbo);
		drm_gem_vram_unpin(gbo);

		drm_gem_object_put_unlocked(afb->obj);
		afb->obj = NULL;
	}
	drm_fb_helper_fini(&vbox->fb_helper);

	drm_framebuffer_unregister_private(&afb->base);
	drm_framebuffer_cleanup(&afb->base);
}