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
struct drm_atomic_state {int dummy; } ;
struct dm_atomic_state {int /*<<< orphan*/ * context; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_release_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_atomic_state_default_clear (struct drm_atomic_state*) ; 
 struct dm_atomic_state* to_dm_atomic_state (struct drm_atomic_state*) ; 

__attribute__((used)) static void
dm_atomic_state_clear(struct drm_atomic_state *state)
{
	struct dm_atomic_state *dm_state = to_dm_atomic_state(state);

	if (dm_state->context) {
		dc_release_state(dm_state->context);
		dm_state->context = NULL;
	}

	drm_atomic_state_default_clear(state);
}