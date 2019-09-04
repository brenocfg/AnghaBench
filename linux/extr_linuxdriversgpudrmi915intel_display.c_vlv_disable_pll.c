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
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DPLL (int) ; 
 int DPLL_INTEGRATED_CRI_CLK_VLV ; 
 int DPLL_INTEGRATED_REF_CLK_VLV ; 
 int DPLL_REF_CLK_ENABLE_VLV ; 
 int DPLL_VGA_MODE_DIS ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PIPE_A ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_pipe_disabled (struct drm_i915_private*,int) ; 

__attribute__((used)) static void vlv_disable_pll(struct drm_i915_private *dev_priv, enum pipe pipe)
{
	u32 val;

	/* Make sure the pipe isn't still relying on us */
	assert_pipe_disabled(dev_priv, pipe);

	val = DPLL_INTEGRATED_REF_CLK_VLV |
		DPLL_REF_CLK_ENABLE_VLV | DPLL_VGA_MODE_DIS;
	if (pipe != PIPE_A)
		val |= DPLL_INTEGRATED_CRI_CLK_VLV;

	I915_WRITE(DPLL(pipe), val);
	POSTING_READ(DPLL(pipe));
}