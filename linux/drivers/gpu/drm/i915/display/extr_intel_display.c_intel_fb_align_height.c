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
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,unsigned int) ; 
 unsigned int intel_tile_height (struct drm_framebuffer const*,int) ; 

unsigned int
intel_fb_align_height(const struct drm_framebuffer *fb,
		      int color_plane, unsigned int height)
{
	unsigned int tile_height = intel_tile_height(fb, color_plane);

	return ALIGN(height, tile_height);
}