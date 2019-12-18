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
struct drm_private_state {int dummy; } ;
struct drm_private_obj {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct drm_private_state*,int /*<<< orphan*/ ,int) ; 

void __drm_atomic_helper_private_obj_duplicate_state(struct drm_private_obj *obj,
						     struct drm_private_state *state)
{
	memcpy(state, obj->state, sizeof(*state));
}