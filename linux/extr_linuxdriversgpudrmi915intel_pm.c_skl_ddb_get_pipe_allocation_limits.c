#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct skl_ddb_entry {int start; unsigned int end; } ;
struct skl_ddb_allocation {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  active; struct drm_crtc* crtc; struct drm_atomic_state* state; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_atomic_state {int active_crtcs; scalar_t__ active_pipe_changes; } ;
struct drm_i915_private {int active_crtcs; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_6__ {struct skl_ddb_entry ddb; } ;
struct TYPE_7__ {TYPE_2__ skl; } ;
struct TYPE_8__ {TYPE_3__ wm; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int drm_crtc_mask (struct drm_crtc*) ; 
 unsigned int hweight32 (int) ; 
 unsigned int intel_get_ddb_size (struct drm_i915_private*,struct intel_crtc_state const*,unsigned int const,int,struct skl_ddb_allocation*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 
 TYPE_4__* to_intel_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
skl_ddb_get_pipe_allocation_limits(struct drm_device *dev,
				   const struct intel_crtc_state *cstate,
				   const unsigned int total_data_rate,
				   struct skl_ddb_allocation *ddb,
				   struct skl_ddb_entry *alloc, /* out */
				   int *num_active /* out */)
{
	struct drm_atomic_state *state = cstate->base.state;
	struct intel_atomic_state *intel_state = to_intel_atomic_state(state);
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_crtc *for_crtc = cstate->base.crtc;
	unsigned int pipe_size, ddb_size;
	int nth_active_pipe;

	if (WARN_ON(!state) || !cstate->base.active) {
		alloc->start = 0;
		alloc->end = 0;
		*num_active = hweight32(dev_priv->active_crtcs);
		return;
	}

	if (intel_state->active_pipe_changes)
		*num_active = hweight32(intel_state->active_crtcs);
	else
		*num_active = hweight32(dev_priv->active_crtcs);

	ddb_size = intel_get_ddb_size(dev_priv, cstate, total_data_rate,
				      *num_active, ddb);

	/*
	 * If the state doesn't change the active CRTC's, then there's
	 * no need to recalculate; the existing pipe allocation limits
	 * should remain unchanged.  Note that we're safe from racing
	 * commits since any racing commit that changes the active CRTC
	 * list would need to grab _all_ crtc locks, including the one
	 * we currently hold.
	 */
	if (!intel_state->active_pipe_changes) {
		/*
		 * alloc may be cleared by clear_intel_crtc_state,
		 * copy from old state to be sure
		 */
		*alloc = to_intel_crtc_state(for_crtc->state)->wm.skl.ddb;
		return;
	}

	nth_active_pipe = hweight32(intel_state->active_crtcs &
				    (drm_crtc_mask(for_crtc) - 1));
	pipe_size = ddb_size / hweight32(intel_state->active_crtcs);
	alloc->start = nth_active_pipe * ddb_size / *num_active;
	alloc->end = alloc->start + pipe_size;
}