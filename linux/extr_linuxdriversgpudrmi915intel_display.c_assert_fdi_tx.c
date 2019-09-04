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
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  FDI_TX_CTL (int) ; 
 int FDI_TX_ENABLE ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int) ; 
 int TRANS_DDI_FUNC_ENABLE ; 
 int intel_pipe_to_cpu_transcoder (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  onoff (int) ; 

__attribute__((used)) static void assert_fdi_tx(struct drm_i915_private *dev_priv,
			  enum pipe pipe, bool state)
{
	bool cur_state;
	enum transcoder cpu_transcoder = intel_pipe_to_cpu_transcoder(dev_priv,
								      pipe);

	if (HAS_DDI(dev_priv)) {
		/* DDI does not have a specific FDI_TX register */
		u32 val = I915_READ(TRANS_DDI_FUNC_CTL(cpu_transcoder));
		cur_state = !!(val & TRANS_DDI_FUNC_ENABLE);
	} else {
		u32 val = I915_READ(FDI_TX_CTL(pipe));
		cur_state = !!(val & FDI_TX_ENABLE);
	}
	I915_STATE_WARN(cur_state != state,
	     "FDI TX state assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
}