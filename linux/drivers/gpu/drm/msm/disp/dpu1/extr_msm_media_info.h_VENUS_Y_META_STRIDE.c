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
#define  COLOR_FMT_NV12_BPP10_UBWC 130 
#define  COLOR_FMT_NV12_UBWC 129 
#define  COLOR_FMT_P010_UBWC 128 
 unsigned int MSM_MEDIA_ALIGN (int,int) ; 
 int MSM_MEDIA_ROUNDUP (int,int) ; 

__attribute__((used)) static unsigned int VENUS_Y_META_STRIDE(int color_fmt, int width)
{
	int y_tile_width = 0, y_meta_stride;

	if (!width)
		return 0;

	switch (color_fmt) {
	case COLOR_FMT_NV12_UBWC:
	case COLOR_FMT_P010_UBWC:
		y_tile_width = 32;
		break;
	case COLOR_FMT_NV12_BPP10_UBWC:
		y_tile_width = 48;
		break;
	default:
		return 0;
	}

	y_meta_stride = MSM_MEDIA_ROUNDUP(width, y_tile_width);
	return MSM_MEDIA_ALIGN(y_meta_stride, 64);
}