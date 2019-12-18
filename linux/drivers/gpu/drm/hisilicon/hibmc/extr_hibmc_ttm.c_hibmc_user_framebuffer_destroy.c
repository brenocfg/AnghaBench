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
struct hibmc_framebuffer {int /*<<< orphan*/  obj; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hibmc_framebuffer*) ; 
 struct hibmc_framebuffer* to_hibmc_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static void hibmc_user_framebuffer_destroy(struct drm_framebuffer *fb)
{
	struct hibmc_framebuffer *hibmc_fb = to_hibmc_framebuffer(fb);

	drm_gem_object_put_unlocked(hibmc_fb->obj);
	drm_framebuffer_cleanup(fb);
	kfree(hibmc_fb);
}