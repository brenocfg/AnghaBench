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
struct komeda_plane_state {struct drm_plane_state base; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_duplicate_state (struct drm_plane*,struct drm_plane_state*) ; 
 struct komeda_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_plane_state *
komeda_plane_atomic_duplicate_state(struct drm_plane *plane)
{
	struct komeda_plane_state *new;

	if (WARN_ON(!plane->state))
		return NULL;

	new = kzalloc(sizeof(*new), GFP_KERNEL);
	if (!new)
		return NULL;

	__drm_atomic_helper_plane_duplicate_state(plane, &new->base);

	return &new->base;
}