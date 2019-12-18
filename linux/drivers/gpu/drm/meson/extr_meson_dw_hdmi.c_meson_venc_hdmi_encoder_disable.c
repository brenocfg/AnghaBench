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

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  ENCI_VIDEO_EN ; 
 int /*<<< orphan*/  ENCP_VIDEO_EN ; 
 int /*<<< orphan*/  VPU_HDMI_SETTING ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 struct meson_dw_hdmi* encoder_to_meson_dw_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_venc_hdmi_encoder_disable(struct drm_encoder *encoder)
{
	struct meson_dw_hdmi *dw_hdmi = encoder_to_meson_dw_hdmi(encoder);
	struct meson_drm *priv = dw_hdmi->priv;

	DRM_DEBUG_DRIVER("\n");

	writel_bits_relaxed(0x3, 0,
			    priv->io_base + _REG(VPU_HDMI_SETTING));

	writel_relaxed(0, priv->io_base + _REG(ENCI_VIDEO_EN));
	writel_relaxed(0, priv->io_base + _REG(ENCP_VIDEO_EN));
}