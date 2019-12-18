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
struct drm_plane {scalar_t__ state; } ;
struct armada_plane_state {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (scalar_t__) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct armada_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 

void armada_plane_reset(struct drm_plane *plane)
{
	struct armada_plane_state *st;
	if (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);
	kfree(plane->state);
	st = kzalloc(sizeof(*st), GFP_KERNEL);
	if (st)
		__drm_atomic_helper_plane_reset(plane, &st->base);
}