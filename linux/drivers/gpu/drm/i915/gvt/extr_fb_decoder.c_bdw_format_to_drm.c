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
#define  DISPPLANE_8BPP 133 
#define  DISPPLANE_BGRX101010 132 
#define  DISPPLANE_BGRX565 131 
#define  DISPPLANE_BGRX888 130 
#define  DISPPLANE_RGBX101010 129 
#define  DISPPLANE_RGBX888 128 

__attribute__((used)) static int bdw_format_to_drm(int format)
{
	int bdw_pixel_formats_index = 6;

	switch (format) {
	case DISPPLANE_8BPP:
		bdw_pixel_formats_index = 0;
		break;
	case DISPPLANE_BGRX565:
		bdw_pixel_formats_index = 1;
		break;
	case DISPPLANE_BGRX888:
		bdw_pixel_formats_index = 2;
		break;
	case DISPPLANE_RGBX101010:
		bdw_pixel_formats_index = 3;
		break;
	case DISPPLANE_BGRX101010:
		bdw_pixel_formats_index = 4;
		break;
	case DISPPLANE_RGBX888:
		bdw_pixel_formats_index = 5;
		break;

	default:
		break;
	}

	return bdw_pixel_formats_index;
}