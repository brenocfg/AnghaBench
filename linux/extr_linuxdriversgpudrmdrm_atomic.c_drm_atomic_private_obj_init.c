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
struct drm_private_state_funcs {int dummy; } ;
struct drm_private_state {int dummy; } ;
struct drm_private_obj {struct drm_private_state_funcs const* funcs; struct drm_private_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct drm_private_obj*,int /*<<< orphan*/ ,int) ; 

void
drm_atomic_private_obj_init(struct drm_private_obj *obj,
			    struct drm_private_state *state,
			    const struct drm_private_state_funcs *funcs)
{
	memset(obj, 0, sizeof(*obj));

	obj->state = state;
	obj->funcs = funcs;
}