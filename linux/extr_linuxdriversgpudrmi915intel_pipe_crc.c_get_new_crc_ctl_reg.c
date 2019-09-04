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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum intel_pipe_crc_source { ____Placeholder_intel_pipe_crc_source } intel_pipe_crc_source ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN2 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN5 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int i8xx_pipe_crc_ctl_reg (int*,int /*<<< orphan*/ *) ; 
 int i9xx_pipe_crc_ctl_reg (struct drm_i915_private*,int,int*,int /*<<< orphan*/ *) ; 
 int ilk_pipe_crc_ctl_reg (int*,int /*<<< orphan*/ *) ; 
 int ivb_pipe_crc_ctl_reg (struct drm_i915_private*,int,int*,int /*<<< orphan*/ *,int) ; 
 int vlv_pipe_crc_ctl_reg (struct drm_i915_private*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_new_crc_ctl_reg(struct drm_i915_private *dev_priv,
			       enum pipe pipe,
			       enum intel_pipe_crc_source *source, u32 *val,
			       bool set_wa)
{
	if (IS_GEN2(dev_priv))
		return i8xx_pipe_crc_ctl_reg(source, val);
	else if (INTEL_GEN(dev_priv) < 5)
		return i9xx_pipe_crc_ctl_reg(dev_priv, pipe, source, val);
	else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		return vlv_pipe_crc_ctl_reg(dev_priv, pipe, source, val);
	else if (IS_GEN5(dev_priv) || IS_GEN6(dev_priv))
		return ilk_pipe_crc_ctl_reg(source, val);
	else
		return ivb_pipe_crc_ctl_reg(dev_priv, pipe, source, val, set_wa);
}