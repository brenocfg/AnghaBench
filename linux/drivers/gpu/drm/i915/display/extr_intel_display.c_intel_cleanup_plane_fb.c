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
struct intel_atomic_state {int rps_interactive; } ;
struct drm_plane_state {int /*<<< orphan*/  state; } ;
struct drm_plane {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_plane_unpin_fb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_rps_mark_interactive (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_plane_state (struct drm_plane_state*) ; 

void
intel_cleanup_plane_fb(struct drm_plane *plane,
		       struct drm_plane_state *old_state)
{
	struct intel_atomic_state *intel_state =
		to_intel_atomic_state(old_state->state);
	struct drm_i915_private *dev_priv = to_i915(plane->dev);

	if (intel_state->rps_interactive) {
		intel_rps_mark_interactive(dev_priv, false);
		intel_state->rps_interactive = false;
	}

	/* Should only be called after a successful intel_prepare_plane_fb()! */
	mutex_lock(&dev_priv->drm.struct_mutex);
	intel_plane_unpin_fb(to_intel_plane_state(old_state));
	mutex_unlock(&dev_priv->drm.struct_mutex);
}