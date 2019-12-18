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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int i9xx_plane; int pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;

/* Variables and functions */
 int DISPLAY_PLANE_ENABLE ; 
 int DISPPLANE_SEL_PIPE_MASK ; 
 int DISPPLANE_SEL_PIPE_SHIFT ; 
 int /*<<< orphan*/  DSPCNTR (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int POWER_DOMAIN_PIPE (int) ; 
 int /*<<< orphan*/  intel_display_power_get_if_enabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i9xx_plane_get_hw_state(struct intel_plane *plane,
				    enum pipe *pipe)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum intel_display_power_domain power_domain;
	enum i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	intel_wakeref_t wakeref;
	bool ret;
	u32 val;

	/*
	 * Not 100% correct for planes that can move between pipes,
	 * but that's only the case for gen2-4 which don't have any
	 * display power wells.
	 */
	power_domain = POWER_DOMAIN_PIPE(plane->pipe);
	wakeref = intel_display_power_get_if_enabled(dev_priv, power_domain);
	if (!wakeref)
		return false;

	val = I915_READ(DSPCNTR(i9xx_plane));

	ret = val & DISPLAY_PLANE_ENABLE;

	if (INTEL_GEN(dev_priv) >= 5)
		*pipe = plane->pipe;
	else
		*pipe = (val & DISPPLANE_SEL_PIPE_MASK) >>
			DISPPLANE_SEL_PIPE_SHIFT;

	intel_display_power_put(dev_priv, power_domain, wakeref);

	return ret;
}