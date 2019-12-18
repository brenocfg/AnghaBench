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
#define  MCURSOR_MODE_128_ARGB_AX 131 
#define  MCURSOR_MODE_256_ARGB_AX 130 
#define  MCURSOR_MODE_64_32B_AX 129 
#define  MCURSOR_MODE_64_ARGB_AX 128 

__attribute__((used)) static int cursor_mode_to_drm(int mode)
{
	int cursor_pixel_formats_index = 4;

	switch (mode) {
	case MCURSOR_MODE_128_ARGB_AX:
		cursor_pixel_formats_index = 0;
		break;
	case MCURSOR_MODE_256_ARGB_AX:
		cursor_pixel_formats_index = 1;
		break;
	case MCURSOR_MODE_64_ARGB_AX:
		cursor_pixel_formats_index = 2;
		break;
	case MCURSOR_MODE_64_32B_AX:
		cursor_pixel_formats_index = 3;
		break;

	default:
		break;
	}

	return cursor_pixel_formats_index;
}