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
#define  G2D_FMT_ARGB1555 135 
#define  G2D_FMT_ARGB4444 134 
#define  G2D_FMT_ARGB8888 133 
#define  G2D_FMT_PACKED_RGB888 132 
#define  G2D_FMT_RGB565 131 
#define  G2D_FMT_XRGB1555 130 
#define  G2D_FMT_XRGB4444 129 
#define  G2D_FMT_XRGB8888 128 

__attribute__((used)) static unsigned long g2d_get_buf_bpp(unsigned int format)
{
	unsigned long bpp;

	switch (format) {
	case G2D_FMT_XRGB8888:
	case G2D_FMT_ARGB8888:
		bpp = 4;
		break;
	case G2D_FMT_RGB565:
	case G2D_FMT_XRGB1555:
	case G2D_FMT_ARGB1555:
	case G2D_FMT_XRGB4444:
	case G2D_FMT_ARGB4444:
		bpp = 2;
		break;
	case G2D_FMT_PACKED_RGB888:
		bpp = 3;
		break;
	default:
		bpp = 1;
		break;
	}

	return bpp;
}