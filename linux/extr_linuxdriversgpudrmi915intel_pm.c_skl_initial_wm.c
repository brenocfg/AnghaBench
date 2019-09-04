#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct skl_ddb_values {int dirty_pipes; } ;
struct TYPE_4__ {scalar_t__ active_changed; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct TYPE_6__ {struct drm_device* dev; } ;
struct intel_crtc {int pipe; TYPE_3__ base; } ;
struct intel_atomic_state {struct skl_ddb_values wm_results; } ;
struct TYPE_5__ {int /*<<< orphan*/  wm_mutex; struct skl_ddb_values skl_hw; } ;
struct drm_i915_private {TYPE_2__ wm; } ;
struct drm_device {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int drm_crtc_mask (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_atomic_update_crtc_wm (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skl_copy_ddb_for_pipe (struct skl_ddb_values*,struct skl_ddb_values*,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skl_initial_wm(struct intel_atomic_state *state,
			   struct intel_crtc_state *cstate)
{
	struct intel_crtc *intel_crtc = to_intel_crtc(cstate->base.crtc);
	struct drm_device *dev = intel_crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct skl_ddb_values *results = &state->wm_results;
	struct skl_ddb_values *hw_vals = &dev_priv->wm.skl_hw;
	enum pipe pipe = intel_crtc->pipe;

	if ((results->dirty_pipes & drm_crtc_mask(&intel_crtc->base)) == 0)
		return;

	mutex_lock(&dev_priv->wm.wm_mutex);

	if (cstate->base.active_changed)
		skl_atomic_update_crtc_wm(state, cstate);

	skl_copy_ddb_for_pipe(hw_vals, results, pipe);

	mutex_unlock(&dev_priv->wm.wm_mutex);
}