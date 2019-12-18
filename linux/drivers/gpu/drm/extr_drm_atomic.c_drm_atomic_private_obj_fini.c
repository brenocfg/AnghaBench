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
struct drm_private_obj {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_1__* funcs; int /*<<< orphan*/  head; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* atomic_destroy_state ) (struct drm_private_obj*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_modeset_lock_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_private_obj*,int /*<<< orphan*/ ) ; 

void
drm_atomic_private_obj_fini(struct drm_private_obj *obj)
{
	list_del(&obj->head);
	obj->funcs->atomic_destroy_state(obj, obj->state);
	drm_modeset_lock_fini(&obj->lock);
}