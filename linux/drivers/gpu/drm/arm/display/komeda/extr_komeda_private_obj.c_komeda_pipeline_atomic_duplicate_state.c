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
struct komeda_pipeline_state {struct drm_private_state obj; scalar_t__ active_comps; } ;
struct drm_private_obj {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_private_obj_duplicate_state (struct drm_private_obj*,struct drm_private_state*) ; 
 struct komeda_pipeline_state* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_private_state *
komeda_pipeline_atomic_duplicate_state(struct drm_private_obj *obj)
{
	struct komeda_pipeline_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KERNEL);
	if (!st)
		return NULL;

	st->active_comps = 0;

	__drm_atomic_helper_private_obj_duplicate_state(obj, &st->obj);

	return &st->obj;
}