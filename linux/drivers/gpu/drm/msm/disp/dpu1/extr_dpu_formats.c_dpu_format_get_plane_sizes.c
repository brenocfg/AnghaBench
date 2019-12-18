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
typedef  scalar_t__ uint32_t ;
struct dpu_hw_fmt_layout {int dummy; } ;
struct dpu_format {int dummy; } ;

/* Variables and functions */
 scalar_t__ DPU_FORMAT_IS_TILE (struct dpu_format const*) ; 
 scalar_t__ DPU_FORMAT_IS_UBWC (struct dpu_format const*) ; 
 scalar_t__ const DPU_MAX_IMG_HEIGHT ; 
 scalar_t__ const DPU_MAX_IMG_WIDTH ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ERANGE ; 
 int _dpu_format_get_plane_sizes_linear (struct dpu_format const*,scalar_t__ const,scalar_t__ const,struct dpu_hw_fmt_layout*,scalar_t__ const*) ; 
 int _dpu_format_get_plane_sizes_ubwc (struct dpu_format const*,scalar_t__ const,scalar_t__ const,struct dpu_hw_fmt_layout*) ; 

__attribute__((used)) static int dpu_format_get_plane_sizes(
		const struct dpu_format *fmt,
		const uint32_t w,
		const uint32_t h,
		struct dpu_hw_fmt_layout *layout,
		const uint32_t *pitches)
{
	if (!layout || !fmt) {
		DRM_ERROR("invalid pointer\n");
		return -EINVAL;
	}

	if ((w > DPU_MAX_IMG_WIDTH) || (h > DPU_MAX_IMG_HEIGHT)) {
		DRM_ERROR("image dimensions outside max range\n");
		return -ERANGE;
	}

	if (DPU_FORMAT_IS_UBWC(fmt) || DPU_FORMAT_IS_TILE(fmt))
		return _dpu_format_get_plane_sizes_ubwc(fmt, w, h, layout);

	return _dpu_format_get_plane_sizes_linear(fmt, w, h, layout, pitches);
}