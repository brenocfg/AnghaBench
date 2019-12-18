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
#define  WIN_COLOR_DEPTH_YCbCr420P 137 
#define  WIN_COLOR_DEPTH_YCbCr422 136 
#define  WIN_COLOR_DEPTH_YCbCr422P 135 
#define  WIN_COLOR_DEPTH_YCbCr422R 134 
#define  WIN_COLOR_DEPTH_YCbCr422RA 133 
#define  WIN_COLOR_DEPTH_YUV420P 132 
#define  WIN_COLOR_DEPTH_YUV422 131 
#define  WIN_COLOR_DEPTH_YUV422P 130 
#define  WIN_COLOR_DEPTH_YUV422R 129 
#define  WIN_COLOR_DEPTH_YUV422RA 128 

bool tegra_plane_format_is_yuv(unsigned int format, bool *planar)
{
	switch (format) {
	case WIN_COLOR_DEPTH_YCbCr422:
	case WIN_COLOR_DEPTH_YUV422:
		if (planar)
			*planar = false;

		return true;

	case WIN_COLOR_DEPTH_YCbCr420P:
	case WIN_COLOR_DEPTH_YUV420P:
	case WIN_COLOR_DEPTH_YCbCr422P:
	case WIN_COLOR_DEPTH_YUV422P:
	case WIN_COLOR_DEPTH_YCbCr422R:
	case WIN_COLOR_DEPTH_YUV422R:
	case WIN_COLOR_DEPTH_YCbCr422RA:
	case WIN_COLOR_DEPTH_YUV422RA:
		if (planar)
			*planar = true;

		return true;
	}

	if (planar)
		*planar = false;

	return false;
}