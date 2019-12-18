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
struct komeda_pipeline_state {int dummy; } ;
struct komeda_pipeline {int /*<<< orphan*/  obj; } ;
struct drm_private_state {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 struct drm_private_state* drm_atomic_get_new_private_obj_state (struct drm_atomic_state*,int /*<<< orphan*/ *) ; 
 struct komeda_pipeline_state* priv_to_pipe_st (struct drm_private_state*) ; 

__attribute__((used)) static struct komeda_pipeline_state *
komeda_pipeline_get_new_state(struct komeda_pipeline *pipe,
			      struct drm_atomic_state *state)
{
	struct drm_private_state *priv_st;

	priv_st = drm_atomic_get_new_private_obj_state(state, &pipe->obj);
	if (priv_st)
		return priv_to_pipe_st(priv_st);
	return NULL;
}