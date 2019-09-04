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
#define  COLOR_FMT_NV12_MVTB 128 
 unsigned int VENUS_UV_SCANLINES (int,int) ; 
 unsigned int VENUS_UV_STRIDE (int,int) ; 
 unsigned int VENUS_Y_SCANLINES (int,int) ; 
 unsigned int VENUS_Y_STRIDE (int,int) ; 

__attribute__((used)) static inline unsigned int VENUS_VIEW2_OFFSET(
	int color_fmt, int width, int height)
{
	unsigned int offset = 0;
	unsigned int y_plane, uv_plane, y_stride,
		uv_stride, y_sclines, uv_sclines;
	if (!width || !height)
		goto invalid_input;

	y_stride = VENUS_Y_STRIDE(color_fmt, width);
	uv_stride = VENUS_UV_STRIDE(color_fmt, width);
	y_sclines = VENUS_Y_SCANLINES(color_fmt, height);
	uv_sclines = VENUS_UV_SCANLINES(color_fmt, height);
	switch (color_fmt) {
	case COLOR_FMT_NV12_MVTB:
		y_plane = y_stride * y_sclines;
		uv_plane = uv_stride * uv_sclines;
		offset = y_plane + uv_plane;
		break;
	default:
		break;
	}
invalid_input:
	return offset;
}