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
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  G4X_AUD_CNTL_ST ; 
 int /*<<< orphan*/  G4X_AUD_VID_DID ; 
 int /*<<< orphan*/  G4X_ELDV_DEVCL_DEVBLC ; 
 int /*<<< orphan*/  G4X_ELDV_DEVCTG ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_AUDIO_DEVBLC ; 
 int /*<<< orphan*/  INTEL_AUDIO_DEVCL ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void g4x_audio_codec_disable(struct intel_encoder *encoder,
				    const struct intel_crtc_state *old_crtc_state,
				    const struct drm_connector_state *old_conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	u32 eldv, tmp;

	DRM_DEBUG_KMS("Disable audio codec\n");

	tmp = I915_READ(G4X_AUD_VID_DID);
	if (tmp == INTEL_AUDIO_DEVBLC || tmp == INTEL_AUDIO_DEVCL)
		eldv = G4X_ELDV_DEVCL_DEVBLC;
	else
		eldv = G4X_ELDV_DEVCTG;

	/* Invalidate ELD */
	tmp = I915_READ(G4X_AUD_CNTL_ST);
	tmp &= ~eldv;
	I915_WRITE(G4X_AUD_CNTL_ST, tmp);
}