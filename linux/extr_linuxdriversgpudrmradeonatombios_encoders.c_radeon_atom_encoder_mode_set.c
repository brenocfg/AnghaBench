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
struct radeon_encoder {int active_device; int encoder_id; int devices; int /*<<< orphan*/  pixel_clock; } ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_DCE4 (struct radeon_device*) ; 
 int ATOM_DEVICE_CV_SUPPORT ; 
 int ATOM_DEVICE_TV_SUPPORT ; 
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int ATOM_ENCODER_MODE_HDMI ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 scalar_t__ ENCODER_MODE_IS_DP (int) ; 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC1 143 
#define  ENCODER_OBJECT_ID_INTERNAL_DAC2 142 
#define  ENCODER_OBJECT_ID_INTERNAL_DDI 141 
#define  ENCODER_OBJECT_ID_INTERNAL_DVO1 140 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1 139 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2 138 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1 137 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA 136 
#define  ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1 135 
#define  ENCODER_OBJECT_ID_INTERNAL_LVDS 134 
#define  ENCODER_OBJECT_ID_INTERNAL_LVTM1 133 
#define  ENCODER_OBJECT_ID_INTERNAL_TMDS1 132 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY 131 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 130 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 129 
#define  ENCODER_OBJECT_ID_INTERNAL_UNIPHY3 128 
 int /*<<< orphan*/  PANEL_ENCODER_ACTION_ENABLE ; 
 int /*<<< orphan*/  atombios_apply_encoder_quirks (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  atombios_dac_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_digital_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_dvo_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int atombios_get_encoder_mode (struct drm_encoder*) ; 
 int /*<<< orphan*/  atombios_tv_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atombios_yuv_setup (struct drm_encoder*,int) ; 
 int /*<<< orphan*/  radeon_atom_encoder_dpms (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 scalar_t__ radeon_audio ; 
 int /*<<< orphan*/  radeon_audio_mode_set (struct drm_encoder*,struct drm_display_mode*) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
radeon_atom_encoder_mode_set(struct drm_encoder *encoder,
			     struct drm_display_mode *mode,
			     struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
	int encoder_mode;

	radeon_encoder->pixel_clock = adjusted_mode->clock;

	/* need to call this here rather than in prepare() since we need some crtc info */
	radeon_atom_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	if (ASIC_IS_AVIVO(rdev) && !ASIC_IS_DCE4(rdev)) {
		if (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT | ATOM_DEVICE_TV_SUPPORT))
			atombios_yuv_setup(encoder, true);
		else
			atombios_yuv_setup(encoder, false);
	}

	switch (radeon_encoder->encoder_id) {
	case ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
	case ENCODER_OBJECT_ID_INTERNAL_LVDS:
	case ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		atombios_digital_setup(encoder, PANEL_ENCODER_ACTION_ENABLE);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	case ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		/* handled in dpms */
		break;
	case ENCODER_OBJECT_ID_INTERNAL_DDI:
	case ENCODER_OBJECT_ID_INTERNAL_DVO1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		atombios_dvo_setup(encoder, ATOM_ENABLE);
		break;
	case ENCODER_OBJECT_ID_INTERNAL_DAC1:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
	case ENCODER_OBJECT_ID_INTERNAL_DAC2:
	case ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		atombios_dac_setup(encoder, ATOM_ENABLE);
		if (radeon_encoder->devices & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT)) {
			if (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT))
				atombios_tv_setup(encoder, ATOM_ENABLE);
			else
				atombios_tv_setup(encoder, ATOM_DISABLE);
		}
		break;
	}

	atombios_apply_encoder_quirks(encoder, adjusted_mode);

	encoder_mode = atombios_get_encoder_mode(encoder);
	if (connector && (radeon_audio != 0) &&
	    ((encoder_mode == ATOM_ENCODER_MODE_HDMI) ||
	     ENCODER_MODE_IS_DP(encoder_mode)))
		radeon_audio_mode_set(encoder, adjusted_mode);
}