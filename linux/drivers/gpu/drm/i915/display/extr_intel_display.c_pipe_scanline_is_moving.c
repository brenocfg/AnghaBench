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
 int DSL_LINEMASK_GEN2 ; 
 int DSL_LINEMASK_GEN3 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  PIPEDSL (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static bool pipe_scanline_is_moving(struct drm_i915_private *dev_priv,
				    enum pipe pipe)
{
	i915_reg_t reg = PIPEDSL(pipe);
	u32 line1, line2;
	u32 line_mask;

	if (IS_GEN(dev_priv, 2))
		line_mask = DSL_LINEMASK_GEN2;
	else
		line_mask = DSL_LINEMASK_GEN3;

	line1 = I915_READ(reg) & line_mask;
	msleep(5);
	line2 = I915_READ(reg) & line_mask;

	return line1 != line2;
}