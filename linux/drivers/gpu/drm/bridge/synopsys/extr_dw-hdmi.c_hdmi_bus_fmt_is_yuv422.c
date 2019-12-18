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
#define  MEDIA_BUS_FMT_UYVY10_1X20 130 
#define  MEDIA_BUS_FMT_UYVY12_1X24 129 
#define  MEDIA_BUS_FMT_UYVY8_1X16 128 

__attribute__((used)) static bool hdmi_bus_fmt_is_yuv422(unsigned int bus_format)
{
	switch (bus_format) {
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_UYVY10_1X20:
	case MEDIA_BUS_FMT_UYVY12_1X24:
		return true;

	default:
		return false;
	}
}