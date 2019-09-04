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
struct tegra_plane_state {int format; int opaque; } ;
struct tegra_plane {int dummy; } ;

/* Variables and functions */
#define  WIN_COLOR_DEPTH_A1B5G5R5 131 
#define  WIN_COLOR_DEPTH_B5G5R5A1 130 
#define  WIN_COLOR_DEPTH_B8G8R8A8 129 
#define  WIN_COLOR_DEPTH_R8G8B8A8 128 
 int tegra_plane_format_get_alpha (int,unsigned int*) ; 

__attribute__((used)) static int tegra_plane_setup_opacity(struct tegra_plane *tegra,
				     struct tegra_plane_state *state)
{
	unsigned int format;
	int err;

	switch (state->format) {
	case WIN_COLOR_DEPTH_B5G5R5A1:
	case WIN_COLOR_DEPTH_A1B5G5R5:
	case WIN_COLOR_DEPTH_R8G8B8A8:
	case WIN_COLOR_DEPTH_B8G8R8A8:
		state->opaque = false;
		break;

	default:
		err = tegra_plane_format_get_alpha(state->format, &format);
		if (err < 0)
			return err;

		state->format = format;
		state->opaque = true;
		break;
	}

	return 0;
}