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
struct dm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_state_default_release (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  kfree (struct dm_atomic_state*) ; 
 struct dm_atomic_state* to_dm_atomic_state (struct drm_atomic_state*) ; 

__attribute__((used)) static void
dm_atomic_state_alloc_free(struct drm_atomic_state *state)
{
	struct dm_atomic_state *dm_state = to_dm_atomic_state(state);
	drm_atomic_state_default_release(state);
	kfree(dm_state);
}