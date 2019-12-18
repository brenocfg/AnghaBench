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
struct intel_plane_state {int dummy; } ;
struct intel_plane {int /*<<< orphan*/  base; } ;
struct intel_atomic_state {int /*<<< orphan*/  base; } ;
struct drm_plane_state {int dummy; } ;

/* Variables and functions */
 struct intel_plane_state* ERR_CAST (struct drm_plane_state*) ; 
 scalar_t__ IS_ERR (struct drm_plane_state*) ; 
 struct drm_plane_state* drm_atomic_get_plane_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct intel_plane_state* to_intel_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static inline struct intel_plane_state *
intel_atomic_get_plane_state(struct intel_atomic_state *state,
				 struct intel_plane *plane)
{
	struct drm_plane_state *ret =
		drm_atomic_get_plane_state(&state->base, &plane->base);

	if (IS_ERR(ret))
		return ERR_CAST(ret);

	return to_intel_plane_state(ret);
}