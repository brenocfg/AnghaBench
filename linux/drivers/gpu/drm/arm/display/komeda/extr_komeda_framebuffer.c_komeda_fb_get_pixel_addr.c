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
typedef  int u32 ;
struct drm_framebuffer {int* offsets; int* pitches; TYPE_1__* format; int /*<<< orphan*/  modifier; } ;
struct komeda_fb {struct drm_framebuffer base; } ;
struct drm_gem_cma_object {int paddr; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int num_planes; int* char_per_block; int hsub; int vsub; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int) ; 
 int drm_format_info_block_width (TYPE_1__*,int) ; 

dma_addr_t
komeda_fb_get_pixel_addr(struct komeda_fb *kfb, int x, int y, int plane)
{
	struct drm_framebuffer *fb = &kfb->base;
	const struct drm_gem_cma_object *obj;
	u32 offset, plane_x, plane_y, block_w, block_sz;

	if (plane >= fb->format->num_planes) {
		DRM_DEBUG_KMS("Out of max plane num.\n");
		return -EINVAL;
	}

	obj = drm_fb_cma_get_gem_obj(fb, plane);

	offset = fb->offsets[plane];
	if (!fb->modifier) {
		block_w = drm_format_info_block_width(fb->format, plane);
		block_sz = fb->format->char_per_block[plane];
		plane_x = x / (plane ? fb->format->hsub : 1);
		plane_y = y / (plane ? fb->format->vsub : 1);

		offset += (plane_x / block_w) * block_sz
			+ plane_y * fb->pitches[plane];
	}

	return obj->paddr + offset;
}