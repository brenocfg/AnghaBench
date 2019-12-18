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
struct drm_rect {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/ * obj; TYPE_2__* format; TYPE_1__* dev; } ;
struct cirrus_device {int cpp; int /*<<< orphan*/  pitch; int /*<<< orphan*/  vram; } ;
struct TYPE_4__ {int* cpp; } ;
struct TYPE_3__ {struct cirrus_device* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ON_ONCE (char*) ; 
 int /*<<< orphan*/  drm_fb_memcpy_dstclip (int /*<<< orphan*/ ,void*,struct drm_framebuffer*,struct drm_rect*) ; 
 int /*<<< orphan*/  drm_fb_xrgb8888_to_rgb565_dstclip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct drm_framebuffer*,struct drm_rect*,int) ; 
 int /*<<< orphan*/  drm_fb_xrgb8888_to_rgb888_dstclip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct drm_framebuffer*,struct drm_rect*) ; 
 void* drm_gem_shmem_vmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_shmem_vunmap (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int cirrus_fb_blit_rect(struct drm_framebuffer *fb,
			       struct drm_rect *rect)
{
	struct cirrus_device *cirrus = fb->dev->dev_private;
	void *vmap;

	vmap = drm_gem_shmem_vmap(fb->obj[0]);
	if (!vmap)
		return -ENOMEM;

	if (cirrus->cpp == fb->format->cpp[0])
		drm_fb_memcpy_dstclip(cirrus->vram,
				      vmap, fb, rect);

	else if (fb->format->cpp[0] == 4 && cirrus->cpp == 2)
		drm_fb_xrgb8888_to_rgb565_dstclip(cirrus->vram,
						  cirrus->pitch,
						  vmap, fb, rect, false);

	else if (fb->format->cpp[0] == 4 && cirrus->cpp == 3)
		drm_fb_xrgb8888_to_rgb888_dstclip(cirrus->vram,
						  cirrus->pitch,
						  vmap, fb, rect);

	else
		WARN_ON_ONCE("cpp mismatch");

	drm_gem_shmem_vunmap(fb->obj[0], vmap);
	return 0;
}