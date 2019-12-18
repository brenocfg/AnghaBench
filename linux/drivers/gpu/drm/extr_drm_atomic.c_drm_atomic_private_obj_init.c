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
struct drm_private_state_funcs {int dummy; } ;
struct drm_private_state {int dummy; } ;
struct drm_private_obj {int /*<<< orphan*/  head; struct drm_private_state_funcs const* funcs; struct drm_private_state* state; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  privobj_list; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_modeset_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct drm_private_obj*,int /*<<< orphan*/ ,int) ; 

void
drm_atomic_private_obj_init(struct drm_device *dev,
			    struct drm_private_obj *obj,
			    struct drm_private_state *state,
			    const struct drm_private_state_funcs *funcs)
{
	memset(obj, 0, sizeof(*obj));

	drm_modeset_lock_init(&obj->lock);

	obj->state = state;
	obj->funcs = funcs;
	list_add_tail(&obj->head, &dev->mode_config.privobj_list);
}