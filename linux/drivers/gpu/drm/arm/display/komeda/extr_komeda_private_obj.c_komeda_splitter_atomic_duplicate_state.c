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
struct TYPE_2__ {struct drm_private_state obj; } ;
struct komeda_splitter_state {TYPE_1__ base; } ;
struct drm_private_obj {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_private_obj_duplicate_state (struct drm_private_obj*,struct drm_private_state*) ; 
 struct komeda_splitter_state* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_component_state_reset (TYPE_1__*) ; 

__attribute__((used)) static struct drm_private_state *
komeda_splitter_atomic_duplicate_state(struct drm_private_obj *obj)
{
	struct komeda_splitter_state *st;

	st = kmemdup(obj->state, sizeof(*st), GFP_KERNEL);
	if (!st)
		return NULL;

	komeda_component_state_reset(&st->base);
	__drm_atomic_helper_private_obj_duplicate_state(obj, &st->base.obj);

	return &st->base.obj;
}