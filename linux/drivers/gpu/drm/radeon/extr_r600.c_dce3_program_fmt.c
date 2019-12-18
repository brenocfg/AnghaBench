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
struct radeon_encoder {int devices; scalar_t__ encoder_id; } ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {scalar_t__ crtc_offset; } ;
struct radeon_connector {int dither; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int dummy; } ;
typedef  enum radeon_connector_dither { ____Placeholder_radeon_connector_dither } radeon_connector_dither ;

/* Variables and functions */
 int ATOM_DEVICE_LCD_SUPPORT ; 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1 ; 
 scalar_t__ ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2 ; 
 scalar_t__ FMT_BIT_DEPTH_CONTROL ; 
 int FMT_SPATIAL_DITHER_DEPTH ; 
 int FMT_SPATIAL_DITHER_EN ; 
 int FMT_TRUNCATE_DEPTH ; 
 int FMT_TRUNCATE_EN ; 
 int RADEON_FMT_DITHER_DISABLE ; 
 int RADEON_FMT_DITHER_ENABLE ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 int radeon_get_monitor_bpc (struct drm_connector*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void dce3_program_fmt(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
	int bpc = 0;
	u32 tmp = 0;
	enum radeon_connector_dither dither = RADEON_FMT_DITHER_DISABLE;

	if (connector) {
		struct radeon_connector *radeon_connector = to_radeon_connector(connector);
		bpc = radeon_get_monitor_bpc(connector);
		dither = radeon_connector->dither;
	}

	/* LVDS FMT is set up by atom */
	if (radeon_encoder->devices & ATOM_DEVICE_LCD_SUPPORT)
		return;

	/* not needed for analog */
	if ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1) ||
	    (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2))
		return;

	if (bpc == 0)
		return;

	switch (bpc) {
	case 6:
		if (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			tmp |= FMT_SPATIAL_DITHER_EN;
		else
			tmp |= FMT_TRUNCATE_EN;
		break;
	case 8:
		if (dither == RADEON_FMT_DITHER_ENABLE)
			/* XXX sort out optimal dither settings */
			tmp |= (FMT_SPATIAL_DITHER_EN | FMT_SPATIAL_DITHER_DEPTH);
		else
			tmp |= (FMT_TRUNCATE_EN | FMT_TRUNCATE_DEPTH);
		break;
	case 10:
	default:
		/* not needed */
		break;
	}

	WREG32(FMT_BIT_DEPTH_CONTROL + radeon_crtc->crtc_offset, tmp);
}