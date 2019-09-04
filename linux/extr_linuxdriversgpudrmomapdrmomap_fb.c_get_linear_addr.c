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
typedef  scalar_t__ u32 ;
struct plane {scalar_t__ dma_addr; } ;
struct omap_framebuffer {struct plane* planes; } ;
struct drm_framebuffer {int* pitches; scalar_t__* offsets; } ;
struct drm_format_info {int* cpp; int hsub; int vsub; } ;

/* Variables and functions */
 struct omap_framebuffer* to_omap_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static u32 get_linear_addr(struct drm_framebuffer *fb,
		const struct drm_format_info *format, int n, int x, int y)
{
	struct omap_framebuffer *omap_fb = to_omap_framebuffer(fb);
	struct plane *plane = &omap_fb->planes[n];
	u32 offset;

	offset = fb->offsets[n]
	       + (x * format->cpp[n] / (n == 0 ? 1 : format->hsub))
	       + (y * fb->pitches[n] / (n == 0 ? 1 : format->vsub));

	return plane->dma_addr + offset;
}