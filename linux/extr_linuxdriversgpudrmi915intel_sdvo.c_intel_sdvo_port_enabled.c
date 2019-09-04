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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int SDVO_ENABLE ; 
 int SDVO_PIPE_SEL_MASK ; 
 int SDVO_PIPE_SEL_MASK_CHV ; 
 int SDVO_PIPE_SEL_MASK_CPT ; 
 int SDVO_PIPE_SEL_SHIFT ; 
 int SDVO_PIPE_SEL_SHIFT_CHV ; 
 int SDVO_PIPE_SEL_SHIFT_CPT ; 

bool intel_sdvo_port_enabled(struct drm_i915_private *dev_priv,
			     i915_reg_t sdvo_reg, enum pipe *pipe)
{
	u32 val;

	val = I915_READ(sdvo_reg);

	/* asserts want to know the pipe even if the port is disabled */
	if (HAS_PCH_CPT(dev_priv))
		*pipe = (val & SDVO_PIPE_SEL_MASK_CPT) >> SDVO_PIPE_SEL_SHIFT_CPT;
	else if (IS_CHERRYVIEW(dev_priv))
		*pipe = (val & SDVO_PIPE_SEL_MASK_CHV) >> SDVO_PIPE_SEL_SHIFT_CHV;
	else
		*pipe = (val & SDVO_PIPE_SEL_MASK) >> SDVO_PIPE_SEL_SHIFT;

	return val & SDVO_ENABLE;
}