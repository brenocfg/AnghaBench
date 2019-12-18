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
struct drm_private_state {int dummy; } ;
struct drm_private_obj {int dummy; } ;
struct drm_atomic_state {int num_private_objs; TYPE_1__* private_objs; } ;
struct TYPE_2__ {struct drm_private_state* old_state; struct drm_private_obj* ptr; } ;

/* Variables and functions */

struct drm_private_state *
drm_atomic_get_old_private_obj_state(struct drm_atomic_state *state,
				     struct drm_private_obj *obj)
{
	int i;

	for (i = 0; i < state->num_private_objs; i++)
		if (obj == state->private_objs[i].ptr)
			return state->private_objs[i].old_state;

	return NULL;
}