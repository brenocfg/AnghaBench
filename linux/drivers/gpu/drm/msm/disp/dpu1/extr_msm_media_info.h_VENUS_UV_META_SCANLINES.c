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

__attribute__((used)) static unsigned int VENUS_UV_META_SCANLINES(int color_fmt, int height)
{
	int uv_tile_height = 0, uv_meta_scanlines;

	if (!height)
		return 0;

	switch (color_fmt) {
	case COLOR_FMT_NV12_UBWC:
		uv_tile_height = 8;
		break;
	case COLOR_FMT_NV12_BPP10_UBWC:
	case COLOR_FMT_P010_UBWC:
		uv_tile_height = 4;
		break;
	default:
		return 0;
	}

	uv_meta_scanlines = MSM_MEDIA_ROUNDUP((height+1)>>1, uv_tile_height);
	return MSM_MEDIA_ALIGN(uv_meta_scanlines, 16);
}