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
struct vc4_ctm_state {struct drm_private_state base; } ;
struct drm_private_obj {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_private_obj_duplicate_state (struct drm_private_obj*,struct drm_private_state*) ; 
 struct vc4_ctm_state* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_private_state *
vc4_ctm_duplicate_state(struct drm_private_obj *obj)
{
	struct vc4_ctm_state *state;

	state = kmemdup(obj->state, sizeof(*state), GFP_KERNEL);
	if (!state)
		return NULL;

	__drm_atomic_helper_private_obj_duplicate_state(obj, &state->base);

	return &state->base;
}