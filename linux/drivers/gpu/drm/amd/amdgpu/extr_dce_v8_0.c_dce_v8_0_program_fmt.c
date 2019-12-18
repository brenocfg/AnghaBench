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
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct amdgpu_encoder {int devices; scalar_t__ encoder_id; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {scalar_t__ crtc_offset; } ;
struct amdgpu_connector {int dither; } ;
typedef  enum amdgpu_connector_dither { ____Placeholder_amdgpu_connector_dither } amdgpu_connector_dither ;

/* Variables and functions */
 int AMDGPU_FMT_DITHER_DISABLE ; 
 int AMDGPU_FMT_DITHER_ENABLE ; 
 int ATOM_DEVICE_LCD_SUPPORT ; 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1 ; 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2 ; 
 int FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK ; 
 int FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK ; 
 int FMT_BIT_DEPTH_CONTROL__FMT_RGB_RANDOM_ENABLE_MASK ; 
 int FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT ; 
 int FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK ; 
 int FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT ; 
 int FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int amdgpu_connector_get_monitor_bpc (struct drm_connector*) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder (struct drm_encoder*) ; 
 scalar_t__ mmFMT_BIT_DEPTH_CONTROL ; 
 struct amdgpu_connector* to_amdgpu_connector (struct drm_connector*) ; 
 struct amdgpu_crtc* to_amdgpu_crtc (int /*<<< orphan*/ ) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v8_0_program_fmt(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
	struct drm_connector *connector = amdgpu_get_connector_for_encoder(encoder);
	int bpc = 0;
	u32 tmp = 0;
	enum amdgpu_connector_dither dither = AMDGPU_FMT_DITHER_DISABLE;

	if (connector) {
		struct amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		bpc = amdgpu_connector_get_monitor_bpc(connector);
		dither = amdgpu_connector->dither;
	}

	/* LVDS/eDP FMT is set up by atom */
	if (amdgpu_encoder->devices & ATOM_DEVICE_LCD_SUPPORT)
		return;

	/* not needed for analog */
	if ((amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1) ||
	    (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2))
		return;

	if (bpc == 0)
		return;

	switch (bpc) {
	case 6:
		if (dither == AMDGPU_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(0 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		else
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(0 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		break;
	case 8:
		if (dither == AMDGPU_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_RGB_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(1 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		else
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(1 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		break;
	case 10:
		if (dither == AMDGPU_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_FRAME_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_HIGHPASS_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_RGB_RANDOM_ENABLE_MASK |
				FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_EN_MASK |
				(2 << FMT_BIT_DEPTH_CONTROL__FMT_SPATIAL_DITHER_DEPTH__SHIFT));
		else
			tmp |= (FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_EN_MASK |
			(2 << FMT_BIT_DEPTH_CONTROL__FMT_TRUNCATE_DEPTH__SHIFT));
		break;
	default:
		/* not needed */
		break;
	}

	WREG32(mmFMT_BIT_DEPTH_CONTROL + amdgpu_crtc->crtc_offset, tmp);
}