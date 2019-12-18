#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct komeda_component_state {int dummy; } ;
struct komeda_component {int /*<<< orphan*/  obj; TYPE_2__* pipeline; } ;
struct drm_private_state {int dummy; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ obj; } ;

/* Variables and functions */
 struct komeda_component_state* ERR_CAST (struct drm_private_state*) ; 
 scalar_t__ IS_ERR (struct drm_private_state*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_private_state* drm_atomic_get_private_obj_state (struct drm_atomic_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 struct komeda_component_state* priv_to_comp_st (struct drm_private_state*) ; 

__attribute__((used)) static struct komeda_component_state *
komeda_component_get_state(struct komeda_component *c,
			   struct drm_atomic_state *state)
{
	struct drm_private_state *priv_st;

	WARN_ON(!drm_modeset_is_locked(&c->pipeline->obj.lock));

	priv_st = drm_atomic_get_private_obj_state(state, &c->obj);
	if (IS_ERR(priv_st))
		return ERR_CAST(priv_st);

	return priv_to_comp_st(priv_st);
}