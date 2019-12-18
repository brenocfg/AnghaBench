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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  CURCNTR (int) ; 
 int CURSOR_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PIPE_A ; 
 int POWER_DOMAIN_PIPE (int) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i845_cursor_get_hw_state(struct intel_plane *plane,
				     enum pipe *pipe)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum intel_display_power_domain power_domain;
	intel_wakeref_t wakeref;
	bool ret;

	power_domain = POWER_DOMAIN_PIPE(PIPE_A);
	wakeref = intel_display_power_get_if_enabled(dev_priv, power_domain);
	if (!wakeref)
		return false;

	ret = I915_READ(CURCNTR(PIPE_A)) & CURSOR_ENABLE;

	*pipe = PIPE_A;

	intel_display_power_put(dev_priv, power_domain, wakeref);

	return ret;
}