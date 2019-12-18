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
struct tegra_plane {int dummy; } ;
struct drm_plane_state {int src_w; int crtc_w; int src_h; int crtc_h; int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int tegra_plane_state_add (struct tegra_plane*,struct drm_plane_state*) ; 
 struct tegra_plane* to_tegra_plane (struct drm_plane*) ; 

__attribute__((used)) static int tegra_cursor_atomic_check(struct drm_plane *plane,
				     struct drm_plane_state *state)
{
	struct tegra_plane *tegra = to_tegra_plane(plane);
	int err;

	/* no need for further checks if the plane is being disabled */
	if (!state->crtc)
		return 0;

	/* scaling not supported for cursor */
	if ((state->src_w >> 16 != state->crtc_w) ||
	    (state->src_h >> 16 != state->crtc_h))
		return -EINVAL;

	/* only square cursors supported */
	if (state->src_w != state->src_h)
		return -EINVAL;

	if (state->crtc_w != 32 && state->crtc_w != 64 &&
	    state->crtc_w != 128 && state->crtc_w != 256)
		return -EINVAL;

	err = tegra_plane_state_add(tegra, state);
	if (err < 0)
		return err;

	return 0;
}