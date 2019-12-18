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
struct sun4i_tcon {int dummy; } ;
struct drm_encoder {int encoder_type; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
#define  DRM_MODE_ENCODER_DSI 132 
#define  DRM_MODE_ENCODER_LVDS 131 
#define  DRM_MODE_ENCODER_NONE 130 
#define  DRM_MODE_ENCODER_TMDS 129 
#define  DRM_MODE_ENCODER_TVDAC 128 
 int /*<<< orphan*/  sun4i_tcon0_mode_set_cpu (struct sun4i_tcon*,struct drm_encoder const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  sun4i_tcon0_mode_set_lvds (struct sun4i_tcon*,struct drm_encoder const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  sun4i_tcon0_mode_set_rgb (struct sun4i_tcon*,struct drm_encoder const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  sun4i_tcon1_mode_set (struct sun4i_tcon*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  sun4i_tcon_set_mux (struct sun4i_tcon*,int,struct drm_encoder const*) ; 

void sun4i_tcon_mode_set(struct sun4i_tcon *tcon,
			 const struct drm_encoder *encoder,
			 const struct drm_display_mode *mode)
{
	switch (encoder->encoder_type) {
	case DRM_MODE_ENCODER_DSI:
		/* DSI is tied to special case of CPU interface */
		sun4i_tcon0_mode_set_cpu(tcon, encoder, mode);
		break;
	case DRM_MODE_ENCODER_LVDS:
		sun4i_tcon0_mode_set_lvds(tcon, encoder, mode);
		break;
	case DRM_MODE_ENCODER_NONE:
		sun4i_tcon0_mode_set_rgb(tcon, encoder, mode);
		sun4i_tcon_set_mux(tcon, 0, encoder);
		break;
	case DRM_MODE_ENCODER_TVDAC:
	case DRM_MODE_ENCODER_TMDS:
		sun4i_tcon1_mode_set(tcon, mode);
		sun4i_tcon_set_mux(tcon, 1, encoder);
		break;
	default:
		DRM_DEBUG_DRIVER("Unknown encoder type, doing nothing...\n");
	}
}