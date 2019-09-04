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
 int MSM_MEDIA_ALIGN (int,int) ; 
 int MSM_MEDIA_ROUNDUP (int,int) ; 

__attribute__((used)) static inline unsigned int VENUS_Y_META_SCANLINES(int color_fmt, int height)
{
	int y_tile_height = 0, y_meta_scanlines = 0;

	if (!height)
		goto invalid_input;

	switch (color_fmt) {
	case COLOR_FMT_NV12_UBWC:
		y_tile_height = 8;
		break;
	case COLOR_FMT_NV12_BPP10_UBWC:
	case COLOR_FMT_P010_UBWC:
		y_tile_height = 4;
		break;
	default:
		goto invalid_input;
	}

	y_meta_scanlines = MSM_MEDIA_ROUNDUP(height, y_tile_height);
	y_meta_scanlines = MSM_MEDIA_ALIGN(y_meta_scanlines, 16);

invalid_input:
	return y_meta_scanlines;
}