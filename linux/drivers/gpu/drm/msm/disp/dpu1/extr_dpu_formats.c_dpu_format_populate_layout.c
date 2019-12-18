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
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_gem_address_space {int dummy; } ;
struct drm_framebuffer {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  pitches; } ;
struct dpu_hw_fmt_layout {int /*<<< orphan*/ * plane_addr; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  plane_addr ;

/* Variables and functions */
 scalar_t__ DPU_FORMAT_IS_TILE (int /*<<< orphan*/ ) ; 
 scalar_t__ DPU_FORMAT_IS_UBWC (int /*<<< orphan*/ ) ; 
 scalar_t__ DPU_MAX_IMG_HEIGHT ; 
 scalar_t__ DPU_MAX_IMG_WIDTH ; 
 int DPU_MAX_PLANES ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ERANGE ; 
 int _dpu_format_populate_addrs_linear (struct msm_gem_address_space*,struct drm_framebuffer*,struct dpu_hw_fmt_layout*) ; 
 int _dpu_format_populate_addrs_ubwc (struct msm_gem_address_space*,struct drm_framebuffer*,struct dpu_hw_fmt_layout*) ; 
 int dpu_format_get_plane_sizes (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct dpu_hw_fmt_layout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msm_framebuffer_format (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  to_dpu_format (int /*<<< orphan*/ ) ; 

int dpu_format_populate_layout(
		struct msm_gem_address_space *aspace,
		struct drm_framebuffer *fb,
		struct dpu_hw_fmt_layout *layout)
{
	uint32_t plane_addr[DPU_MAX_PLANES];
	int i, ret;

	if (!fb || !layout) {
		DRM_ERROR("invalid arguments\n");
		return -EINVAL;
	}

	if ((fb->width > DPU_MAX_IMG_WIDTH) ||
			(fb->height > DPU_MAX_IMG_HEIGHT)) {
		DRM_ERROR("image dimensions outside max range\n");
		return -ERANGE;
	}

	layout->format = to_dpu_format(msm_framebuffer_format(fb));

	/* Populate the plane sizes etc via get_format */
	ret = dpu_format_get_plane_sizes(layout->format, fb->width, fb->height,
			layout, fb->pitches);
	if (ret)
		return ret;

	for (i = 0; i < DPU_MAX_PLANES; ++i)
		plane_addr[i] = layout->plane_addr[i];

	/* Populate the addresses given the fb */
	if (DPU_FORMAT_IS_UBWC(layout->format) ||
			DPU_FORMAT_IS_TILE(layout->format))
		ret = _dpu_format_populate_addrs_ubwc(aspace, fb, layout);
	else
		ret = _dpu_format_populate_addrs_linear(aspace, fb, layout);

	/* check if anything changed */
	if (!ret && !memcmp(plane_addr, layout->plane_addr, sizeof(plane_addr)))
		ret = -EAGAIN;

	return ret;
}