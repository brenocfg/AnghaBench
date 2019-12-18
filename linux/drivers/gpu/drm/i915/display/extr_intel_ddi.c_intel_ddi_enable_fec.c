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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; TYPE_1__ base; } ;
struct intel_crtc_state {int /*<<< orphan*/  fec_enable; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TP_CTL (int) ; 
 int /*<<< orphan*/  DP_TP_CTL_FEC_ENABLE ; 
 int /*<<< orphan*/  DP_TP_STATUS (int) ; 
 int /*<<< orphan*/  DP_TP_STATUS_FEC_ENABLE_LIVE ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_enable_fec(struct intel_encoder *encoder,
				 const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	u32 val;

	if (!crtc_state->fec_enable)
		return;

	val = I915_READ(DP_TP_CTL(port));
	val |= DP_TP_CTL_FEC_ENABLE;
	I915_WRITE(DP_TP_CTL(port), val);

	if (intel_de_wait_for_set(dev_priv, DP_TP_STATUS(port),
				  DP_TP_STATUS_FEC_ENABLE_LIVE, 1))
		DRM_ERROR("Timed out waiting for FEC Enable Status\n");
}