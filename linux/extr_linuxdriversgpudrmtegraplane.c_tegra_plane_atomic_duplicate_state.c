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
struct drm_plane_state {int dummy; } ;
struct tegra_plane_state {struct drm_plane_state base; int /*<<< orphan*/ * blending; int /*<<< orphan*/  opaque; int /*<<< orphan*/  bottom_up; int /*<<< orphan*/  swap; int /*<<< orphan*/  format; int /*<<< orphan*/  tiling; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_duplicate_state (struct drm_plane*,struct drm_plane_state*) ; 
 struct tegra_plane_state* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct tegra_plane_state* to_tegra_plane_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_plane_state *
tegra_plane_atomic_duplicate_state(struct drm_plane *plane)
{
	struct tegra_plane_state *state = to_tegra_plane_state(plane->state);
	struct tegra_plane_state *copy;
	unsigned int i;

	copy = kmalloc(sizeof(*copy), GFP_KERNEL);
	if (!copy)
		return NULL;

	__drm_atomic_helper_plane_duplicate_state(plane, &copy->base);
	copy->tiling = state->tiling;
	copy->format = state->format;
	copy->swap = state->swap;
	copy->bottom_up = state->bottom_up;
	copy->opaque = state->opaque;

	for (i = 0; i < 2; i++)
		copy->blending[i] = state->blending[i];

	return &copy->base;
}