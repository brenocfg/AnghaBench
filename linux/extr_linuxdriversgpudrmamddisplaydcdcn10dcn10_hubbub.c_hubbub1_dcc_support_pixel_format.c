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
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;

/* Variables and functions */
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 132 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 131 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 130 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 129 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 128 

__attribute__((used)) static bool hubbub1_dcc_support_pixel_format(
		enum surface_pixel_format format,
		unsigned int *bytes_per_element)
{
	/* DML: get_bytes_per_element */
	switch (format) {
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
	case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		*bytes_per_element = 2;
		return true;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		*bytes_per_element = 4;
		return true;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		*bytes_per_element = 8;
		return true;
	default:
		return false;
	}
}