#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct udl_framebuffer {TYPE_1__* obj; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct udl_framebuffer*) ; 
 struct udl_framebuffer* to_udl_fb (struct drm_framebuffer*) ; 

__attribute__((used)) static void udl_user_framebuffer_destroy(struct drm_framebuffer *fb)
{
	struct udl_framebuffer *ufb = to_udl_fb(fb);

	if (ufb->obj)
		drm_gem_object_put_unlocked(&ufb->obj->base);

	drm_framebuffer_cleanup(fb);
	kfree(ufb);
}