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
#define  COLOR_FMT_NV12 134 
#define  COLOR_FMT_NV12_BPP10_UBWC 133 
#define  COLOR_FMT_NV12_MVTB 132 
#define  COLOR_FMT_NV12_UBWC 131 
#define  COLOR_FMT_NV21 130 
#define  COLOR_FMT_P010 129 
#define  COLOR_FMT_P010_UBWC 128 
 unsigned int MSM_MEDIA_ALIGN (int,unsigned int) ; 

__attribute__((used)) static inline unsigned int VENUS_Y_STRIDE(int color_fmt, int width)
{
	unsigned int alignment, stride = 0;

	if (!width)
		goto invalid_input;

	switch (color_fmt) {
	case COLOR_FMT_NV21:
	case COLOR_FMT_NV12:
	case COLOR_FMT_NV12_MVTB:
	case COLOR_FMT_NV12_UBWC:
		alignment = 128;
		stride = MSM_MEDIA_ALIGN(width, alignment);
		break;
	case COLOR_FMT_NV12_BPP10_UBWC:
		alignment = 256;
		stride = MSM_MEDIA_ALIGN(width, 192);
		stride = MSM_MEDIA_ALIGN(stride * 4/3, alignment);
		break;
	case COLOR_FMT_P010_UBWC:
		alignment = 256;
		stride = MSM_MEDIA_ALIGN(width * 2, alignment);
		break;
	case COLOR_FMT_P010:
		alignment = 128;
		stride = MSM_MEDIA_ALIGN(width*2, alignment);
		break;
	default:
		break;
	}
invalid_input:
	return stride;
}