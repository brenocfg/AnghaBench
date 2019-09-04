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
typedef  int u32 ;
struct drm_framebuffer {scalar_t__ modifier; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 int intel_tile_width_bytes (struct drm_framebuffer const*,int) ; 

__attribute__((used)) static u32
intel_fb_stride_alignment(const struct drm_framebuffer *fb, int plane)
{
	if (fb->modifier == DRM_FORMAT_MOD_LINEAR)
		return 64;
	else
		return intel_tile_width_bytes(fb, plane);
}