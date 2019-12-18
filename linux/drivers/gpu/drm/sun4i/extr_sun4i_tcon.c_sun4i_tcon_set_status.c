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
struct sun4i_tcon {int /*<<< orphan*/  regs; } ;
struct drm_encoder {int encoder_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
#define  DRM_MODE_ENCODER_DSI 132 
#define  DRM_MODE_ENCODER_LVDS 131 
#define  DRM_MODE_ENCODER_NONE 130 
#define  DRM_MODE_ENCODER_TMDS 129 
#define  DRM_MODE_ENCODER_TVDAC 128 
 int /*<<< orphan*/  SUN4I_TCON_GCTL_REG ; 
 int /*<<< orphan*/  SUN4I_TCON_GCTL_TCON_ENABLE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_tcon_channel_set_status (struct sun4i_tcon*,int,int) ; 
 int /*<<< orphan*/  sun4i_tcon_lvds_set_status (struct sun4i_tcon*,struct drm_encoder const*,int) ; 

void sun4i_tcon_set_status(struct sun4i_tcon *tcon,
			   const struct drm_encoder *encoder,
			   bool enabled)
{
	bool is_lvds = false;
	int channel;

	switch (encoder->encoder_type) {
	case DRM_MODE_ENCODER_LVDS:
		is_lvds = true;
		/* Fallthrough */
	case DRM_MODE_ENCODER_DSI:
	case DRM_MODE_ENCODER_NONE:
		channel = 0;
		break;
	case DRM_MODE_ENCODER_TMDS:
	case DRM_MODE_ENCODER_TVDAC:
		channel = 1;
		break;
	default:
		DRM_DEBUG_DRIVER("Unknown encoder type, doing nothing...\n");
		return;
	}

	if (is_lvds && !enabled)
		sun4i_tcon_lvds_set_status(tcon, encoder, false);

	regmap_update_bits(tcon->regs, SUN4I_TCON_GCTL_REG,
			   SUN4I_TCON_GCTL_TCON_ENABLE,
			   enabled ? SUN4I_TCON_GCTL_TCON_ENABLE : 0);

	if (is_lvds && enabled)
		sun4i_tcon_lvds_set_status(tcon, encoder, true);

	sun4i_tcon_channel_set_status(tcon, channel, enabled);
}