#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int normalized_zpos; } ;
struct tegra_plane_state {TYPE_3__* blending; TYPE_2__ base; scalar_t__ opaque; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct tegra_plane {TYPE_1__ base; } ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ alpha; } ;

/* Variables and functions */
 int BLEND_COLOR_KEY_NONE ; 
 int BLEND_CONTROL_ALPHA ; 
 int BLEND_CONTROL_DEPENDENT ; 
 int BLEND_WEIGHT0 (int) ; 
 int BLEND_WEIGHT1 (int) ; 
 int /*<<< orphan*/  DC_WIN_BLEND_1WIN ; 
 int /*<<< orphan*/  DC_WIN_BLEND_2WIN_X ; 
 int /*<<< orphan*/  DC_WIN_BLEND_2WIN_Y ; 
 int /*<<< orphan*/  DC_WIN_BLEND_3WIN_XY ; 
 int /*<<< orphan*/  DC_WIN_BLEND_NOKEY ; 
 int /*<<< orphan*/  tegra_plane_writel (struct tegra_plane*,int,int /*<<< orphan*/ ) ; 
 struct tegra_plane_state* to_tegra_plane_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_plane_setup_blending_legacy(struct tegra_plane *plane)
{
	u32 background[3] = {
		BLEND_WEIGHT1(0) | BLEND_WEIGHT0(0) | BLEND_COLOR_KEY_NONE,
		BLEND_WEIGHT1(0) | BLEND_WEIGHT0(0) | BLEND_COLOR_KEY_NONE,
		BLEND_WEIGHT1(0) | BLEND_WEIGHT0(0) | BLEND_COLOR_KEY_NONE,
	};
	u32 foreground = BLEND_WEIGHT1(255) | BLEND_WEIGHT0(255) |
			 BLEND_COLOR_KEY_NONE;
	u32 blendnokey = BLEND_WEIGHT1(255) | BLEND_WEIGHT0(255);
	struct tegra_plane_state *state;
	u32 blending[2];
	unsigned int i;

	/* disable blending for non-overlapping case */
	tegra_plane_writel(plane, blendnokey, DC_WIN_BLEND_NOKEY);
	tegra_plane_writel(plane, foreground, DC_WIN_BLEND_1WIN);

	state = to_tegra_plane_state(plane->base.state);

	if (state->opaque) {
		/*
		 * Since custom fix-weight blending isn't utilized and weight
		 * of top window is set to max, we can enforce dependent
		 * blending which in this case results in transparent bottom
		 * window if top window is opaque and if top window enables
		 * alpha blending, then bottom window is getting alpha value
		 * of 1 minus the sum of alpha components of the overlapping
		 * plane.
		 */
		background[0] |= BLEND_CONTROL_DEPENDENT;
		background[1] |= BLEND_CONTROL_DEPENDENT;

		/*
		 * The region where three windows overlap is the intersection
		 * of the two regions where two windows overlap. It contributes
		 * to the area if all of the windows on top of it have an alpha
		 * component.
		 */
		switch (state->base.normalized_zpos) {
		case 0:
			if (state->blending[0].alpha &&
			    state->blending[1].alpha)
				background[2] |= BLEND_CONTROL_DEPENDENT;
			break;

		case 1:
			background[2] |= BLEND_CONTROL_DEPENDENT;
			break;
		}
	} else {
		/*
		 * Enable alpha blending if pixel format has an alpha
		 * component.
		 */
		foreground |= BLEND_CONTROL_ALPHA;

		/*
		 * If any of the windows on top of this window is opaque, it
		 * will completely conceal this window within that area. If
		 * top window has an alpha component, it is blended over the
		 * bottom window.
		 */
		for (i = 0; i < 2; i++) {
			if (state->blending[i].alpha &&
			    state->blending[i].top)
				background[i] |= BLEND_CONTROL_DEPENDENT;
		}

		switch (state->base.normalized_zpos) {
		case 0:
			if (state->blending[0].alpha &&
			    state->blending[1].alpha)
				background[2] |= BLEND_CONTROL_DEPENDENT;
			break;

		case 1:
			/*
			 * When both middle and topmost windows have an alpha,
			 * these windows a mixed together and then the result
			 * is blended over the bottom window.
			 */
			if (state->blending[0].alpha &&
			    state->blending[0].top)
				background[2] |= BLEND_CONTROL_ALPHA;

			if (state->blending[1].alpha &&
			    state->blending[1].top)
				background[2] |= BLEND_CONTROL_ALPHA;
			break;
		}
	}

	switch (state->base.normalized_zpos) {
	case 0:
		tegra_plane_writel(plane, background[0], DC_WIN_BLEND_2WIN_X);
		tegra_plane_writel(plane, background[1], DC_WIN_BLEND_2WIN_Y);
		tegra_plane_writel(plane, background[2], DC_WIN_BLEND_3WIN_XY);
		break;

	case 1:
		/*
		 * If window B / C is topmost, then X / Y registers are
		 * matching the order of blending[...] state indices,
		 * otherwise a swap is required.
		 */
		if (!state->blending[0].top && state->blending[1].top) {
			blending[0] = foreground;
			blending[1] = background[1];
		} else {
			blending[0] = background[0];
			blending[1] = foreground;
		}

		tegra_plane_writel(plane, blending[0], DC_WIN_BLEND_2WIN_X);
		tegra_plane_writel(plane, blending[1], DC_WIN_BLEND_2WIN_Y);
		tegra_plane_writel(plane, background[2], DC_WIN_BLEND_3WIN_XY);
		break;

	case 2:
		tegra_plane_writel(plane, foreground, DC_WIN_BLEND_2WIN_X);
		tegra_plane_writel(plane, foreground, DC_WIN_BLEND_2WIN_Y);
		tegra_plane_writel(plane, foreground, DC_WIN_BLEND_3WIN_XY);
		break;
	}
}