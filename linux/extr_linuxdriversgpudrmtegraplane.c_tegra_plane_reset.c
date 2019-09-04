#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  normalized_zpos; int /*<<< orphan*/  zpos; struct drm_plane* plane; } ;
struct tegra_plane_state {TYPE_1__ base; } ;
struct tegra_plane {int /*<<< orphan*/  index; } ;
struct drm_plane {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 struct tegra_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct tegra_plane* to_tegra_plane (struct drm_plane*) ; 

__attribute__((used)) static void tegra_plane_reset(struct drm_plane *plane)
{
	struct tegra_plane *p = to_tegra_plane(plane);
	struct tegra_plane_state *state;

	if (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);

	kfree(plane->state);
	plane->state = NULL;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state) {
		plane->state = &state->base;
		plane->state->plane = plane;
		plane->state->zpos = p->index;
		plane->state->normalized_zpos = p->index;
	}
}