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

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPT_TRANSCONF ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  TRANS_CHICKEN2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANS_CHICKEN2_TIMING_OVERRIDE ; 
 int /*<<< orphan*/  TRANS_ENABLE ; 
 int /*<<< orphan*/  TRANS_STATE_ENABLE ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void lpt_disable_pch_transcoder(struct drm_i915_private *dev_priv)
{
	u32 val;

	val = I915_READ(LPT_TRANSCONF);
	val &= ~TRANS_ENABLE;
	I915_WRITE(LPT_TRANSCONF, val);
	/* wait for PCH transcoder off, transcoder state */
	if (intel_de_wait_for_clear(dev_priv, LPT_TRANSCONF,
				    TRANS_STATE_ENABLE, 50))
		DRM_ERROR("Failed to disable PCH transcoder\n");

	/* Workaround: clear timing override bit. */
	val = I915_READ(TRANS_CHICKEN2(PIPE_A));
	val &= ~TRANS_CHICKEN2_TIMING_OVERRIDE;
	I915_WRITE(TRANS_CHICKEN2(PIPE_A), val);
}