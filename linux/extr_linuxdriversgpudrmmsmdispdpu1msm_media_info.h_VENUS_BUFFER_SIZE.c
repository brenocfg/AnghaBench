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

/* Variables and functions */
#define  COLOR_FMT_NV12 138 
#define  COLOR_FMT_NV12_BPP10_UBWC 137 
#define  COLOR_FMT_NV12_MVTB 136 
#define  COLOR_FMT_NV12_UBWC 135 
#define  COLOR_FMT_NV21 134 
#define  COLOR_FMT_P010 133 
#define  COLOR_FMT_P010_UBWC 132 
#define  COLOR_FMT_RGB565_UBWC 131 
#define  COLOR_FMT_RGBA1010102_UBWC 130 
#define  COLOR_FMT_RGBA8888 129 
#define  COLOR_FMT_RGBA8888_UBWC 128 
 unsigned int MSM_MEDIA_ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  MSM_MEDIA_MAX (unsigned int const,int) ; 
 unsigned int VENUS_EXTRADATA_SIZE (int,int) ; 
 unsigned int VENUS_RGB_META_SCANLINES (int,int) ; 
 unsigned int VENUS_RGB_META_STRIDE (int,int) ; 
 unsigned int VENUS_RGB_SCANLINES (int,int) ; 
 unsigned int VENUS_RGB_STRIDE (int,int) ; 
 unsigned int VENUS_UV_META_SCANLINES (int,int) ; 
 unsigned int VENUS_UV_META_STRIDE (int,int) ; 
 unsigned int VENUS_UV_SCANLINES (int,int) ; 
 unsigned int VENUS_UV_STRIDE (int,int) ; 
 unsigned int VENUS_Y_META_SCANLINES (int,int) ; 
 unsigned int VENUS_Y_META_STRIDE (int,int) ; 
 unsigned int VENUS_Y_SCANLINES (int,int) ; 
 unsigned int VENUS_Y_STRIDE (int,int) ; 

__attribute__((used)) static inline unsigned int VENUS_BUFFER_SIZE(
	int color_fmt, int width, int height)
{
	const unsigned int extra_size = VENUS_EXTRADATA_SIZE(width, height);
	unsigned int uv_alignment = 0, size = 0;
	unsigned int y_plane, uv_plane, y_stride,
		uv_stride, y_sclines, uv_sclines;
	unsigned int y_ubwc_plane = 0, uv_ubwc_plane = 0;
	unsigned int y_meta_stride = 0, y_meta_scanlines = 0;
	unsigned int uv_meta_stride = 0, uv_meta_scanlines = 0;
	unsigned int y_meta_plane = 0, uv_meta_plane = 0;
	unsigned int rgb_stride = 0, rgb_scanlines = 0;
	unsigned int rgb_plane = 0, rgb_ubwc_plane = 0, rgb_meta_plane = 0;
	unsigned int rgb_meta_stride = 0, rgb_meta_scanlines = 0;

	if (!width || !height)
		goto invalid_input;

	y_stride = VENUS_Y_STRIDE(color_fmt, width);
	uv_stride = VENUS_UV_STRIDE(color_fmt, width);
	y_sclines = VENUS_Y_SCANLINES(color_fmt, height);
	uv_sclines = VENUS_UV_SCANLINES(color_fmt, height);
	rgb_stride = VENUS_RGB_STRIDE(color_fmt, width);
	rgb_scanlines = VENUS_RGB_SCANLINES(color_fmt, height);

	switch (color_fmt) {
	case COLOR_FMT_NV21:
	case COLOR_FMT_NV12:
	case COLOR_FMT_P010:
		uv_alignment = 4096;
		y_plane = y_stride * y_sclines;
		uv_plane = uv_stride * uv_sclines + uv_alignment;
		size = y_plane + uv_plane +
				MSM_MEDIA_MAX(extra_size, 8 * y_stride);
		size = MSM_MEDIA_ALIGN(size, 4096);
		break;
	case COLOR_FMT_NV12_MVTB:
		uv_alignment = 4096;
		y_plane = y_stride * y_sclines;
		uv_plane = uv_stride * uv_sclines + uv_alignment;
		size = y_plane + uv_plane;
		size = 2 * size + extra_size;
		size = MSM_MEDIA_ALIGN(size, 4096);
		break;
	case COLOR_FMT_NV12_UBWC:
		y_sclines = VENUS_Y_SCANLINES(color_fmt, (height+1)>>1);
		y_ubwc_plane = MSM_MEDIA_ALIGN(y_stride * y_sclines, 4096);
		uv_sclines = VENUS_UV_SCANLINES(color_fmt, (height+1)>>1);
		uv_ubwc_plane = MSM_MEDIA_ALIGN(uv_stride * uv_sclines, 4096);
		y_meta_stride = VENUS_Y_META_STRIDE(color_fmt, width);
		y_meta_scanlines =
			VENUS_Y_META_SCANLINES(color_fmt, (height+1)>>1);
		y_meta_plane = MSM_MEDIA_ALIGN(
			y_meta_stride * y_meta_scanlines, 4096);
		uv_meta_stride = VENUS_UV_META_STRIDE(color_fmt, width);
		uv_meta_scanlines =
			VENUS_UV_META_SCANLINES(color_fmt, (height+1)>>1);
		uv_meta_plane = MSM_MEDIA_ALIGN(uv_meta_stride *
			uv_meta_scanlines, 4096);

		size = (y_ubwc_plane + uv_ubwc_plane + y_meta_plane +
			uv_meta_plane)*2 +
			MSM_MEDIA_MAX(extra_size + 8192, 48 * y_stride);
		size = MSM_MEDIA_ALIGN(size, 4096);
		break;
	case COLOR_FMT_NV12_BPP10_UBWC:
		y_ubwc_plane = MSM_MEDIA_ALIGN(y_stride * y_sclines, 4096);
		uv_ubwc_plane = MSM_MEDIA_ALIGN(uv_stride * uv_sclines, 4096);
		y_meta_stride = VENUS_Y_META_STRIDE(color_fmt, width);
		y_meta_scanlines = VENUS_Y_META_SCANLINES(color_fmt, height);
		y_meta_plane = MSM_MEDIA_ALIGN(
				y_meta_stride * y_meta_scanlines, 4096);
		uv_meta_stride = VENUS_UV_META_STRIDE(color_fmt, width);
		uv_meta_scanlines = VENUS_UV_META_SCANLINES(color_fmt, height);
		uv_meta_plane = MSM_MEDIA_ALIGN(uv_meta_stride *
					uv_meta_scanlines, 4096);

		size = y_ubwc_plane + uv_ubwc_plane + y_meta_plane +
			uv_meta_plane +
			MSM_MEDIA_MAX(extra_size + 8192, 48 * y_stride);
		size = MSM_MEDIA_ALIGN(size, 4096);
		break;
	case COLOR_FMT_P010_UBWC:
		y_ubwc_plane = MSM_MEDIA_ALIGN(y_stride * y_sclines, 4096);
		uv_ubwc_plane = MSM_MEDIA_ALIGN(uv_stride * uv_sclines, 4096);
		y_meta_stride = VENUS_Y_META_STRIDE(color_fmt, width);
		y_meta_scanlines = VENUS_Y_META_SCANLINES(color_fmt, height);
		y_meta_plane = MSM_MEDIA_ALIGN(
				y_meta_stride * y_meta_scanlines, 4096);
		uv_meta_stride = VENUS_UV_META_STRIDE(color_fmt, width);
		uv_meta_scanlines = VENUS_UV_META_SCANLINES(color_fmt, height);
		uv_meta_plane = MSM_MEDIA_ALIGN(uv_meta_stride *
					uv_meta_scanlines, 4096);

		size = y_ubwc_plane + uv_ubwc_plane + y_meta_plane +
			uv_meta_plane;
		size = MSM_MEDIA_ALIGN(size, 4096);
		break;
	case COLOR_FMT_RGBA8888:
		rgb_plane = MSM_MEDIA_ALIGN(rgb_stride  * rgb_scanlines, 4096);
		size = rgb_plane;
		size =  MSM_MEDIA_ALIGN(size, 4096);
		break;
	case COLOR_FMT_RGBA8888_UBWC:
	case COLOR_FMT_RGBA1010102_UBWC:
	case COLOR_FMT_RGB565_UBWC:
		rgb_ubwc_plane = MSM_MEDIA_ALIGN(rgb_stride * rgb_scanlines,
							4096);
		rgb_meta_stride = VENUS_RGB_META_STRIDE(color_fmt, width);
		rgb_meta_scanlines = VENUS_RGB_META_SCANLINES(color_fmt,
					height);
		rgb_meta_plane = MSM_MEDIA_ALIGN(rgb_meta_stride *
					rgb_meta_scanlines, 4096);
		size = rgb_ubwc_plane + rgb_meta_plane;
		size = MSM_MEDIA_ALIGN(size, 4096);
		break;
	default:
		break;
	}
invalid_input:
	return size;
}