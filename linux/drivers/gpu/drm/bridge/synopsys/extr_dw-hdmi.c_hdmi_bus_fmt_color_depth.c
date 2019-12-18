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
#define  MEDIA_BUS_FMT_RGB101010_1X30 142 
#define  MEDIA_BUS_FMT_RGB121212_1X36 141 
#define  MEDIA_BUS_FMT_RGB161616_1X48 140 
#define  MEDIA_BUS_FMT_RGB888_1X24 139 
#define  MEDIA_BUS_FMT_UYVY10_1X20 138 
#define  MEDIA_BUS_FMT_UYVY12_1X24 137 
#define  MEDIA_BUS_FMT_UYVY8_1X16 136 
#define  MEDIA_BUS_FMT_UYYVYY10_0_5X30 135 
#define  MEDIA_BUS_FMT_UYYVYY12_0_5X36 134 
#define  MEDIA_BUS_FMT_UYYVYY16_0_5X48 133 
#define  MEDIA_BUS_FMT_UYYVYY8_0_5X24 132 
#define  MEDIA_BUS_FMT_YUV10_1X30 131 
#define  MEDIA_BUS_FMT_YUV12_1X36 130 
#define  MEDIA_BUS_FMT_YUV16_1X48 129 
#define  MEDIA_BUS_FMT_YUV8_1X24 128 

__attribute__((used)) static int hdmi_bus_fmt_color_depth(unsigned int bus_format)
{
	switch (bus_format) {
	case MEDIA_BUS_FMT_RGB888_1X24:
	case MEDIA_BUS_FMT_YUV8_1X24:
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_UYYVYY8_0_5X24:
		return 8;

	case MEDIA_BUS_FMT_RGB101010_1X30:
	case MEDIA_BUS_FMT_YUV10_1X30:
	case MEDIA_BUS_FMT_UYVY10_1X20:
	case MEDIA_BUS_FMT_UYYVYY10_0_5X30:
		return 10;

	case MEDIA_BUS_FMT_RGB121212_1X36:
	case MEDIA_BUS_FMT_YUV12_1X36:
	case MEDIA_BUS_FMT_UYVY12_1X24:
	case MEDIA_BUS_FMT_UYYVYY12_0_5X36:
		return 12;

	case MEDIA_BUS_FMT_RGB161616_1X48:
	case MEDIA_BUS_FMT_YUV16_1X48:
	case MEDIA_BUS_FMT_UYYVYY16_0_5X48:
		return 16;

	default:
		return 0;
	}
}