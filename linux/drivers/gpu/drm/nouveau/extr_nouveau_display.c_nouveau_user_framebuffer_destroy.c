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
struct nouveau_framebuffer {TYPE_2__* nvbo; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nouveau_framebuffer*) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static void
nouveau_user_framebuffer_destroy(struct drm_framebuffer *drm_fb)
{
	struct nouveau_framebuffer *fb = nouveau_framebuffer(drm_fb);

	if (fb->nvbo)
		drm_gem_object_put_unlocked(&fb->nvbo->bo.base);

	drm_framebuffer_cleanup(drm_fb);
	kfree(fb);
}