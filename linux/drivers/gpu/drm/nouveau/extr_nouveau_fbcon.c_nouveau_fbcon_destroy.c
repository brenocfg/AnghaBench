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
struct nouveau_framebuffer {int /*<<< orphan*/  base; scalar_t__ nvbo; int /*<<< orphan*/  vma; } ;
struct TYPE_3__ {int /*<<< orphan*/  fb; } ;
struct nouveau_fbdev {TYPE_1__ helper; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_helper_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_fb_helper_unregister_fbi (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_framebuffer_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_bo_unmap (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (scalar_t__) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_vma_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nouveau_fbcon_destroy(struct drm_device *dev, struct nouveau_fbdev *fbcon)
{
	struct nouveau_framebuffer *nouveau_fb = nouveau_framebuffer(fbcon->helper.fb);

	drm_fb_helper_unregister_fbi(&fbcon->helper);
	drm_fb_helper_fini(&fbcon->helper);

	if (nouveau_fb && nouveau_fb->nvbo) {
		nouveau_vma_del(&nouveau_fb->vma);
		nouveau_bo_unmap(nouveau_fb->nvbo);
		nouveau_bo_unpin(nouveau_fb->nvbo);
		drm_framebuffer_put(&nouveau_fb->base);
	}

	return 0;
}