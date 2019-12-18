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
struct meson_dw_hdmi {struct meson_drm* priv; } ;
struct meson_drm {scalar_t__ io_base; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VPU_HDMI_FMT_CTRL ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int drm_match_cea_mode (struct drm_display_mode*) ; 
 int /*<<< orphan*/  dw_hdmi_set_vclk (struct meson_dw_hdmi*,struct drm_display_mode*) ; 
 struct meson_dw_hdmi* encoder_to_meson_dw_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  meson_venc_hdmi_mode_set (struct meson_drm*,int,struct drm_display_mode*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_venc_hdmi_encoder_mode_set(struct drm_encoder *encoder,
				   struct drm_display_mode *mode,
				   struct drm_display_mode *adjusted_mode)
{
	struct meson_dw_hdmi *dw_hdmi = encoder_to_meson_dw_hdmi(encoder);
	struct meson_drm *priv = dw_hdmi->priv;
	int vic = drm_match_cea_mode(mode);

	DRM_DEBUG_DRIVER("\"%s\" vic %d\n", mode->name, vic);

	/* VENC + VENC-DVI Mode setup */
	meson_venc_hdmi_mode_set(priv, vic, mode);

	/* VCLK Set clock */
	dw_hdmi_set_vclk(dw_hdmi, mode);

	/* Setup YUV444 to HDMI-TX, no 10bit diphering */
	writel_relaxed(0, priv->io_base + _REG(VPU_HDMI_FMT_CTRL));
}