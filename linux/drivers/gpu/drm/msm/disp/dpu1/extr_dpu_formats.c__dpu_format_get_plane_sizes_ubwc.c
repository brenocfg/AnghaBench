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
typedef  int uint32_t ;
struct dpu_hw_fmt_layout {int width; int height; int num_planes; int* plane_pitch; void** plane_size; int /*<<< orphan*/  total_size; struct dpu_format const* format; } ;
struct TYPE_2__ {int /*<<< orphan*/  pixel_format; } ;
struct dpu_format {int num_planes; TYPE_1__ base; } ;

/* Variables and functions */
 int DPU_FORMAT_IS_UBWC (struct dpu_format const*) ; 
 scalar_t__ DPU_FORMAT_IS_YUV (struct dpu_format const*) ; 
 int DPU_MAX_PLANES ; 
 int /*<<< orphan*/  DPU_UBWC_PLANE_SIZE_ALIGNMENT ; 
 int /*<<< orphan*/  DRM_ERROR (char*,char*) ; 
 int EINVAL ; 
 void* MSM_MEDIA_ALIGN (int,int /*<<< orphan*/ ) ; 
 int VENUS_RGB_META_SCANLINES (int,int const) ; 
 int VENUS_RGB_META_STRIDE (int,int const) ; 
 int VENUS_RGB_SCANLINES (int,int const) ; 
 int VENUS_RGB_STRIDE (int,int const) ; 
 int VENUS_UV_META_SCANLINES (int,int const) ; 
 int VENUS_UV_META_STRIDE (int,int const) ; 
 int VENUS_UV_SCANLINES (int,int const) ; 
 int VENUS_UV_STRIDE (int,int const) ; 
 int VENUS_Y_META_SCANLINES (int,int const) ; 
 int VENUS_Y_META_STRIDE (int,int const) ; 
 int VENUS_Y_SCANLINES (int,int const) ; 
 int VENUS_Y_STRIDE (int,int const) ; 
 int _dpu_format_get_media_color_ubwc (struct dpu_format const*) ; 
 int /*<<< orphan*/  memset (struct dpu_hw_fmt_layout*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _dpu_format_get_plane_sizes_ubwc(
		const struct dpu_format *fmt,
		const uint32_t width,
		const uint32_t height,
		struct dpu_hw_fmt_layout *layout)
{
	int i;
	int color;
	bool meta = DPU_FORMAT_IS_UBWC(fmt);

	memset(layout, 0, sizeof(struct dpu_hw_fmt_layout));
	layout->format = fmt;
	layout->width = width;
	layout->height = height;
	layout->num_planes = fmt->num_planes;

	color = _dpu_format_get_media_color_ubwc(fmt);
	if (color < 0) {
		DRM_ERROR("UBWC format not supported for fmt: %4.4s\n",
			(char *)&fmt->base.pixel_format);
		return -EINVAL;
	}

	if (DPU_FORMAT_IS_YUV(layout->format)) {
		uint32_t y_sclines, uv_sclines;
		uint32_t y_meta_scanlines = 0;
		uint32_t uv_meta_scanlines = 0;

		layout->num_planes = 2;
		layout->plane_pitch[0] = VENUS_Y_STRIDE(color, width);
		y_sclines = VENUS_Y_SCANLINES(color, height);
		layout->plane_size[0] = MSM_MEDIA_ALIGN(layout->plane_pitch[0] *
			y_sclines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

		layout->plane_pitch[1] = VENUS_UV_STRIDE(color, width);
		uv_sclines = VENUS_UV_SCANLINES(color, height);
		layout->plane_size[1] = MSM_MEDIA_ALIGN(layout->plane_pitch[1] *
			uv_sclines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

		if (!meta)
			goto done;

		layout->num_planes += 2;
		layout->plane_pitch[2] = VENUS_Y_META_STRIDE(color, width);
		y_meta_scanlines = VENUS_Y_META_SCANLINES(color, height);
		layout->plane_size[2] = MSM_MEDIA_ALIGN(layout->plane_pitch[2] *
			y_meta_scanlines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

		layout->plane_pitch[3] = VENUS_UV_META_STRIDE(color, width);
		uv_meta_scanlines = VENUS_UV_META_SCANLINES(color, height);
		layout->plane_size[3] = MSM_MEDIA_ALIGN(layout->plane_pitch[3] *
			uv_meta_scanlines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

	} else {
		uint32_t rgb_scanlines, rgb_meta_scanlines;

		layout->num_planes = 1;

		layout->plane_pitch[0] = VENUS_RGB_STRIDE(color, width);
		rgb_scanlines = VENUS_RGB_SCANLINES(color, height);
		layout->plane_size[0] = MSM_MEDIA_ALIGN(layout->plane_pitch[0] *
			rgb_scanlines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);

		if (!meta)
			goto done;
		layout->num_planes += 2;
		layout->plane_pitch[2] = VENUS_RGB_META_STRIDE(color, width);
		rgb_meta_scanlines = VENUS_RGB_META_SCANLINES(color, height);
		layout->plane_size[2] = MSM_MEDIA_ALIGN(layout->plane_pitch[2] *
			rgb_meta_scanlines, DPU_UBWC_PLANE_SIZE_ALIGNMENT);
	}

done:
	for (i = 0; i < DPU_MAX_PLANES; i++)
		layout->total_size += layout->plane_size[i];

	return 0;
}