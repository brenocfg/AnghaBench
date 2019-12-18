#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int cpu_transcoder; scalar_t__ double_wide; TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {int pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IS_I830 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPECONF (int) ; 
 int PIPECONF_DOUBLE_WIDE ; 
 int PIPECONF_ENABLE ; 
 int /*<<< orphan*/  assert_planes_disabled (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_wait_for_pipe_off (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_intel_pipe_disable (struct intel_crtc*) ; 

__attribute__((used)) static void intel_disable_pipe(const struct intel_crtc_state *old_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(old_crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	enum transcoder cpu_transcoder = old_crtc_state->cpu_transcoder;
	enum pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 val;

	DRM_DEBUG_KMS("disabling pipe %c\n", pipe_name(pipe));

	/*
	 * Make sure planes won't keep trying to pump pixels to us,
	 * or we might hang the display.
	 */
	assert_planes_disabled(crtc);

	trace_intel_pipe_disable(crtc);

	reg = PIPECONF(cpu_transcoder);
	val = I915_READ(reg);
	if ((val & PIPECONF_ENABLE) == 0)
		return;

	/*
	 * Double wide has implications for planes
	 * so best keep it disabled when not needed.
	 */
	if (old_crtc_state->double_wide)
		val &= ~PIPECONF_DOUBLE_WIDE;

	/* Don't disable pipe or pipe PLLs if needed */
	if (!IS_I830(dev_priv))
		val &= ~PIPECONF_ENABLE;

	I915_WRITE(reg, val);
	if ((val & PIPECONF_ENABLE) == 0)
		intel_wait_for_pipe_off(old_crtc_state);
}