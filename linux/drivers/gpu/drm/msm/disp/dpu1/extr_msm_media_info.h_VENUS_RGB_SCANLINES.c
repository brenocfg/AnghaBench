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
#define  COLOR_FMT_RGB565_UBWC 131 
#define  COLOR_FMT_RGBA1010102_UBWC 130 
#define  COLOR_FMT_RGBA8888 129 
#define  COLOR_FMT_RGBA8888_UBWC 128 
 unsigned int MSM_MEDIA_ALIGN (int,unsigned int) ; 

__attribute__((used)) static unsigned int VENUS_RGB_SCANLINES(int color_fmt, int height)
{
	unsigned int alignment = 0;

	if (!height)
		return 0;

	switch (color_fmt) {
	case COLOR_FMT_RGBA8888:
		alignment = 32;
		break;
	case COLOR_FMT_RGBA8888_UBWC:
	case COLOR_FMT_RGBA1010102_UBWC:
	case COLOR_FMT_RGB565_UBWC:
		alignment = 16;
		break;
	default:
		return 0;
	}

	return MSM_MEDIA_ALIGN(height, alignment);
}