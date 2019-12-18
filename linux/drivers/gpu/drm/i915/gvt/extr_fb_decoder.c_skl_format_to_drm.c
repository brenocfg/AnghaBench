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
 int EINVAL ; 
#define  PLANE_CTL_FORMAT_INDEXED 132 
#define  PLANE_CTL_FORMAT_RGB_565 131 
#define  PLANE_CTL_FORMAT_XRGB_2101010 130 
#define  PLANE_CTL_FORMAT_XRGB_8888 129 
#define  PLANE_CTL_FORMAT_YUV422 128 

__attribute__((used)) static int skl_format_to_drm(int format, bool rgb_order, bool alpha,
	int yuv_order)
{
	int skl_pixel_formats_index = 12;

	switch (format) {
	case PLANE_CTL_FORMAT_INDEXED:
		skl_pixel_formats_index = 4;
		break;
	case PLANE_CTL_FORMAT_RGB_565:
		skl_pixel_formats_index = 5;
		break;
	case PLANE_CTL_FORMAT_XRGB_8888:
		if (rgb_order)
			skl_pixel_formats_index = alpha ? 6 : 7;
		else
			skl_pixel_formats_index = alpha ? 8 : 9;
		break;
	case PLANE_CTL_FORMAT_XRGB_2101010:
		skl_pixel_formats_index = rgb_order ? 10 : 11;
		break;
	case PLANE_CTL_FORMAT_YUV422:
		skl_pixel_formats_index = yuv_order >> 16;
		if (skl_pixel_formats_index > 3)
			return -EINVAL;
		break;

	default:
		break;
	}

	return skl_pixel_formats_index;
}