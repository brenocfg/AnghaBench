#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {int dummy; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct drm_plane_state base; } ;
struct armada_overlay_state {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_duplicate_state (struct drm_plane*,struct drm_plane_state*) ; 
 struct armada_overlay_state* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct drm_plane_state *
armada_overlay_duplicate_state(struct drm_plane *plane)
{
	struct armada_overlay_state *state;

	if (WARN_ON(!plane->state))
		return NULL;

	state = kmemdup(plane->state, sizeof(*state), GFP_KERNEL);
	if (state)
		__drm_atomic_helper_plane_duplicate_state(plane,
							  &state->base.base);
	return &state->base.base;
}