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
struct drm_plane {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_helper_plane_destroy_state (struct drm_plane*,struct drm_plane_state*) ; 
 TYPE_1__* to_intel_plane_state (struct drm_plane_state*) ; 

void
intel_plane_destroy_state(struct drm_plane *plane,
			  struct drm_plane_state *state)
{
	WARN_ON(to_intel_plane_state(state)->vma);

	drm_atomic_helper_plane_destroy_state(plane, state);
}