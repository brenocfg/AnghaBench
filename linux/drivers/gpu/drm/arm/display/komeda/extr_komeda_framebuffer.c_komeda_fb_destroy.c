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
typedef  size_t u32 ;
struct komeda_fb {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/ * obj; TYPE_1__* format; } ;
struct TYPE_2__ {size_t num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct komeda_fb*) ; 
 struct komeda_fb* to_kfb (struct drm_framebuffer*) ; 

__attribute__((used)) static void komeda_fb_destroy(struct drm_framebuffer *fb)
{
	struct komeda_fb *kfb = to_kfb(fb);
	u32 i;

	for (i = 0; i < fb->format->num_planes; i++)
		drm_gem_object_put_unlocked(fb->obj[i]);

	drm_framebuffer_cleanup(fb);
	kfree(kfb);
}