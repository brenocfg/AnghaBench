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
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCH_TRANSCONF (int) ; 
 int /*<<< orphan*/  TRANS_CHICKEN2 (int) ; 
 int /*<<< orphan*/  TRANS_CHICKEN2_TIMING_OVERRIDE ; 
 int /*<<< orphan*/  TRANS_ENABLE ; 
 int /*<<< orphan*/  TRANS_STATE_ENABLE ; 
 int /*<<< orphan*/  assert_fdi_rx_disabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_fdi_tx_disabled (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  assert_pch_ports_disabled (struct drm_i915_private*,int) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 

__attribute__((used)) static void ironlake_disable_pch_transcoder(struct drm_i915_private *dev_priv,
					    enum pipe pipe)
{
	i915_reg_t reg;
	u32 val;

	/* FDI relies on the transcoder */
	assert_fdi_tx_disabled(dev_priv, pipe);
	assert_fdi_rx_disabled(dev_priv, pipe);

	/* Ports must be off as well */
	assert_pch_ports_disabled(dev_priv, pipe);

	reg = PCH_TRANSCONF(pipe);
	val = I915_READ(reg);
	val &= ~TRANS_ENABLE;
	I915_WRITE(reg, val);
	/* wait for PCH transcoder off, transcoder state */
	if (intel_de_wait_for_clear(dev_priv, reg, TRANS_STATE_ENABLE, 50))
		DRM_ERROR("failed to disable transcoder %c\n", pipe_name(pipe));

	if (HAS_PCH_CPT(dev_priv)) {
		/* Workaround: Clear the timing override chicken bit again. */
		reg = TRANS_CHICKEN2(pipe);
		val = I915_READ(reg);
		val &= ~TRANS_CHICKEN2_TIMING_OVERRIDE;
		I915_WRITE(reg, val);
	}
}