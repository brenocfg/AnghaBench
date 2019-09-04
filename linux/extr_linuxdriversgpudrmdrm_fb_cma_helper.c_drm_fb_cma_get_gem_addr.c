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
struct drm_plane_state {int src_x; int src_y; } ;
struct drm_gem_cma_object {scalar_t__ paddr; } ;
struct drm_framebuffer {int* pitches; TYPE_1__* format; scalar_t__* offsets; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int* cpp; } ;

/* Variables and functions */
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,unsigned int) ; 

dma_addr_t drm_fb_cma_get_gem_addr(struct drm_framebuffer *fb,
				   struct drm_plane_state *state,
				   unsigned int plane)
{
	struct drm_gem_cma_object *obj;
	dma_addr_t paddr;

	obj = drm_fb_cma_get_gem_obj(fb, plane);
	if (!obj)
		return 0;

	paddr = obj->paddr + fb->offsets[plane];
	paddr += fb->format->cpp[plane] * (state->src_x >> 16);
	paddr += fb->pitches[plane] * (state->src_y >> 16);

	return paddr;
}