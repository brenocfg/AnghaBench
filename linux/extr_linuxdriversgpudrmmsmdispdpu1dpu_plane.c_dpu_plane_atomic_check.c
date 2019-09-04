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
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_PLANE (int /*<<< orphan*/ ,char*) ; 
 int dpu_plane_sspp_atomic_check (struct drm_plane*,struct drm_plane_state*) ; 
 int /*<<< orphan*/  to_dpu_plane (struct drm_plane*) ; 

__attribute__((used)) static int dpu_plane_atomic_check(struct drm_plane *plane,
		struct drm_plane_state *state)
{
	if (!state->fb)
		return 0;

	DPU_DEBUG_PLANE(to_dpu_plane(plane), "\n");

	return dpu_plane_sspp_atomic_check(plane, state);
}