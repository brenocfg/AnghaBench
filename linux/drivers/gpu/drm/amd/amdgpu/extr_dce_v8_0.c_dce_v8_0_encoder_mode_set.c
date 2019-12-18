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
struct drm_encoder {int /*<<< orphan*/  crtc; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct amdgpu_encoder {int /*<<< orphan*/  pixel_clock; } ;

/* Variables and functions */
 scalar_t__ ATOM_ENCODER_MODE_HDMI ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_dpms (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_atombios_encoder_get_encoder_mode (struct drm_encoder*) ; 
 int /*<<< orphan*/  dce_v8_0_afmt_enable (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  dce_v8_0_afmt_setmode (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  dce_v8_0_set_interleave (int /*<<< orphan*/ ,struct drm_display_mode*) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
dce_v8_0_encoder_mode_set(struct drm_encoder *encoder,
			  struct drm_display_mode *mode,
			  struct drm_display_mode *adjusted_mode)
{
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);

	amdgpu_encoder->pixel_clock = adjusted_mode->clock;

	/* need to call this here rather than in prepare() since we need some crtc info */
	amdgpu_atombios_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	/* set scaler clears this on some chips */
	dce_v8_0_set_interleave(encoder->crtc, mode);

	if (amdgpu_atombios_encoder_get_encoder_mode(encoder) == ATOM_ENCODER_MODE_HDMI) {
		dce_v8_0_afmt_enable(encoder, true);
		dce_v8_0_afmt_setmode(encoder, adjusted_mode);
	}
}