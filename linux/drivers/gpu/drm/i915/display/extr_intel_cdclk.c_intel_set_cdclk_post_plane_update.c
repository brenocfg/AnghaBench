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
struct intel_cdclk_state {scalar_t__ cdclk; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int INVALID_PIPE ; 
 int /*<<< orphan*/  intel_set_cdclk (struct drm_i915_private*,struct intel_cdclk_state const*,int) ; 

void
intel_set_cdclk_post_plane_update(struct drm_i915_private *dev_priv,
				  const struct intel_cdclk_state *old_state,
				  const struct intel_cdclk_state *new_state,
				  enum pipe pipe)
{
	if (pipe != INVALID_PIPE && old_state->cdclk > new_state->cdclk)
		intel_set_cdclk(dev_priv, new_state, pipe);
}