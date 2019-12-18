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
 unsigned int WIN_COLOR_DEPTH_A1B5G5R5 ; 
 unsigned int WIN_COLOR_DEPTH_B5G5R5A1 ; 
#define  WIN_COLOR_DEPTH_B5G5R5X1 132 
#define  WIN_COLOR_DEPTH_B5G6R5 131 
 unsigned int WIN_COLOR_DEPTH_B8G8R8A8 ; 
#define  WIN_COLOR_DEPTH_B8G8R8X8 130 
 unsigned int WIN_COLOR_DEPTH_R8G8B8A8 ; 
#define  WIN_COLOR_DEPTH_R8G8B8X8 129 
#define  WIN_COLOR_DEPTH_X1B5G5R5 128 
 scalar_t__ tegra_plane_format_is_yuv (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_plane_format_get_alpha(unsigned int opaque,
					unsigned int *alpha)
{
	if (tegra_plane_format_is_yuv(opaque, NULL)) {
		*alpha = opaque;
		return 0;
	}

	switch (opaque) {
	case WIN_COLOR_DEPTH_B5G5R5X1:
		*alpha = WIN_COLOR_DEPTH_B5G5R5A1;
		return 0;

	case WIN_COLOR_DEPTH_X1B5G5R5:
		*alpha = WIN_COLOR_DEPTH_A1B5G5R5;
		return 0;

	case WIN_COLOR_DEPTH_R8G8B8X8:
		*alpha = WIN_COLOR_DEPTH_R8G8B8A8;
		return 0;

	case WIN_COLOR_DEPTH_B8G8R8X8:
		*alpha = WIN_COLOR_DEPTH_B8G8R8A8;
		return 0;

	case WIN_COLOR_DEPTH_B5G6R5:
		*alpha = opaque;
		return 0;
	}

	return -EINVAL;
}