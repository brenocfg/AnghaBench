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
struct komeda_pipeline_state {int dummy; } ;
struct komeda_pipeline {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {struct drm_atomic_state* state; } ;
struct komeda_crtc_state {int /*<<< orphan*/  active_pipes; int /*<<< orphan*/  affected_pipes; TYPE_1__ base; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct komeda_pipeline_state*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ has_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct komeda_pipeline_state* komeda_pipeline_get_new_state (struct komeda_pipeline*,struct drm_atomic_state*) ; 
 struct komeda_pipeline_state* komeda_pipeline_get_state_and_set_crtc (struct komeda_pipeline*,struct drm_atomic_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  komeda_pipeline_unbound_components (struct komeda_pipeline*,struct komeda_pipeline_state*) ; 

int komeda_release_unclaimed_resources(struct komeda_pipeline *pipe,
				       struct komeda_crtc_state *kcrtc_st)
{
	struct drm_atomic_state *drm_st = kcrtc_st->base.state;
	struct komeda_pipeline_state *st;

	/* ignore the pipeline which is not affected */
	if (!pipe || !has_bit(pipe->id, kcrtc_st->affected_pipes))
		return 0;

	if (has_bit(pipe->id, kcrtc_st->active_pipes))
		st = komeda_pipeline_get_new_state(pipe, drm_st);
	else
		st = komeda_pipeline_get_state_and_set_crtc(pipe, drm_st, NULL);

	if (WARN_ON(IS_ERR_OR_NULL(st)))
		return -EINVAL;

	komeda_pipeline_unbound_components(pipe, st);

	return 0;
}