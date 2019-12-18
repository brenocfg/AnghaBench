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
struct vc4_plane_state {int /*<<< orphan*/  base; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,int /*<<< orphan*/ *) ; 
 struct vc4_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_plane_reset(struct drm_plane *plane)
{
	struct vc4_plane_state *vc4_state;

	WARN_ON(plane->state);

	vc4_state = kzalloc(sizeof(*vc4_state), GFP_KERNEL);
	if (!vc4_state)
		return;

	__drm_atomic_helper_plane_reset(plane, &vc4_state->base);
}