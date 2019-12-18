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
struct komeda_pipeline_state {int /*<<< orphan*/  active_comps; void* binding_user; } ;
struct komeda_component_state {int /*<<< orphan*/  active_comps; void* binding_user; } ;
struct komeda_component {int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  pipeline; } ;
struct drm_crtc {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBUSY ; 
 struct komeda_pipeline_state* ERR_CAST (struct komeda_pipeline_state*) ; 
 struct komeda_pipeline_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct komeda_pipeline_state*) ; 
 scalar_t__ is_switching_user (void*,void*) ; 
 struct komeda_pipeline_state* komeda_component_get_state (struct komeda_component*,struct drm_atomic_state*) ; 
 struct komeda_pipeline_state* komeda_pipeline_get_state_and_set_crtc (int /*<<< orphan*/ ,struct drm_atomic_state*,struct drm_crtc*) ; 

__attribute__((used)) static struct komeda_component_state *
komeda_component_get_state_and_set_user(struct komeda_component *c,
					struct drm_atomic_state *state,
					void *user,
					struct drm_crtc *crtc)
{
	struct komeda_pipeline_state *pipe_st;
	struct komeda_component_state *st;

	/* First check if the pipeline is available */
	pipe_st = komeda_pipeline_get_state_and_set_crtc(c->pipeline,
							 state, crtc);
	if (IS_ERR(pipe_st))
		return ERR_CAST(pipe_st);

	st = komeda_component_get_state(c, state);
	if (IS_ERR(st))
		return st;

	/* check if the component has been occupied */
	if (is_switching_user(user, st->binding_user)) {
		DRM_DEBUG_ATOMIC("required %s is busy.\n", c->name);
		return ERR_PTR(-EBUSY);
	}

	st->binding_user = user;
	/* mark the component as active if user is valid */
	if (st->binding_user)
		pipe_st->active_comps |= BIT(c->id);

	return st;
}