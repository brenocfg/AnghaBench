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
struct vbox_framebuffer {scalar_t__ obj; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct drm_framebuffer*) ; 
 struct vbox_framebuffer* to_vbox_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static void vbox_user_framebuffer_destroy(struct drm_framebuffer *fb)
{
	struct vbox_framebuffer *vbox_fb = to_vbox_framebuffer(fb);

	if (vbox_fb->obj)
		drm_gem_object_put_unlocked(vbox_fb->obj);

	drm_framebuffer_cleanup(fb);
	kfree(fb);
}