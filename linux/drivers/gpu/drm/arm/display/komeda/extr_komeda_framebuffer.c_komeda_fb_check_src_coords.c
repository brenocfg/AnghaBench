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
struct drm_framebuffer {scalar_t__ width; scalar_t__ height; struct drm_format_info* format; } ;
struct komeda_fb {struct drm_framebuffer base; } ;
struct drm_format_info {scalar_t__ hsub; scalar_t__ vsub; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,...) ; 
 int EINVAL ; 
 scalar_t__ drm_format_info_block_height (struct drm_format_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_format_info_block_width (struct drm_format_info*,int /*<<< orphan*/ ) ; 

int komeda_fb_check_src_coords(const struct komeda_fb *kfb,
			       u32 src_x, u32 src_y, u32 src_w, u32 src_h)
{
	const struct drm_framebuffer *fb = &kfb->base;
	const struct drm_format_info *info = fb->format;
	u32 block_w = drm_format_info_block_width(fb->format, 0);
	u32 block_h = drm_format_info_block_height(fb->format, 0);

	if ((src_x + src_w > fb->width) || (src_y + src_h > fb->height)) {
		DRM_DEBUG_ATOMIC("Invalid source coordinate.\n");
		return -EINVAL;
	}

	if ((src_x % info->hsub) || (src_w % info->hsub) ||
	    (src_y % info->vsub) || (src_h % info->vsub)) {
		DRM_DEBUG_ATOMIC("Wrong subsampling dimension x:%d, y:%d, w:%d, h:%d for format: %x.\n",
				 src_x, src_y, src_w, src_h, info->format);
		return -EINVAL;
	}

	if ((src_x % block_w) || (src_w % block_w) ||
	    (src_y % block_h) || (src_h % block_h)) {
		DRM_DEBUG_ATOMIC("x:%d, y:%d, w:%d, h:%d should be multiple of block_w/h for format: %x.\n",
				 src_x, src_y, src_w, src_h, info->format);
		return -EINVAL;
	}

	return 0;
}