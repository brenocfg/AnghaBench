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
typedef  int /*<<< orphan*/  u32 ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_2__ {int num_planes; } ;

/* Variables and functions */
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 int /*<<< orphan*/  intel_fb_pitch (struct drm_framebuffer const*,int,unsigned int) ; 
 int /*<<< orphan*/  intel_fb_stride_alignment (struct drm_framebuffer const*,int) ; 
 int /*<<< orphan*/  intel_tile_height (struct drm_framebuffer const*,int) ; 

u32 skl_plane_stride(const struct drm_framebuffer *fb, int plane,
		     unsigned int rotation)
{
	u32 stride;

	if (plane >= fb->format->num_planes)
		return 0;

	stride = intel_fb_pitch(fb, plane, rotation);

	/*
	 * The stride is either expressed as a multiple of 64 bytes chunks for
	 * linear buffers or in number of tiles for tiled buffers.
	 */
	if (drm_rotation_90_or_270(rotation))
		stride /= intel_tile_height(fb, plane);
	else
		stride /= intel_fb_stride_alignment(fb, plane);

	return stride;
}