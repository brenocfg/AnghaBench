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
struct sun4i_tv {int /*<<< orphan*/  regs; } ;
struct sun4i_crtc {int /*<<< orphan*/  engine; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  SUN4I_TVE_EN_ENABLE ; 
 int /*<<< orphan*/  SUN4I_TVE_EN_REG ; 
 struct sun4i_crtc* drm_crtc_to_sun4i_crtc (int /*<<< orphan*/ ) ; 
 struct sun4i_tv* drm_encoder_to_sun4i_tv (struct drm_encoder*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_engine_apply_color_correction (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun4i_tv_enable(struct drm_encoder *encoder)
{
	struct sun4i_tv *tv = drm_encoder_to_sun4i_tv(encoder);
	struct sun4i_crtc *crtc = drm_crtc_to_sun4i_crtc(encoder->crtc);

	DRM_DEBUG_DRIVER("Enabling the TV Output\n");

	sunxi_engine_apply_color_correction(crtc->engine);

	regmap_update_bits(tv->regs, SUN4I_TVE_EN_REG,
			   SUN4I_TVE_EN_ENABLE,
			   SUN4I_TVE_EN_ENABLE);
}