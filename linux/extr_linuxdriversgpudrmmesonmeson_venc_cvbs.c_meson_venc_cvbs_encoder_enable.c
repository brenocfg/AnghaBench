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
struct meson_venc_cvbs {struct meson_drm* priv; } ;
struct meson_drm {int /*<<< orphan*/  hhi; scalar_t__ io_base; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  HHI_VDAC_CNTL0 ; 
 int /*<<< orphan*/  HHI_VDAC_CNTL1 ; 
 int /*<<< orphan*/  VENC_VDAC_DACSEL0 ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 struct meson_venc_cvbs* encoder_to_meson_venc_cvbs (struct drm_encoder*) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,char*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_venc_cvbs_encoder_enable(struct drm_encoder *encoder)
{
	struct meson_venc_cvbs *meson_venc_cvbs =
					encoder_to_meson_venc_cvbs(encoder);
	struct meson_drm *priv = meson_venc_cvbs->priv;

	/* VDAC0 source is not from ATV */
	writel_bits_relaxed(BIT(5), 0, priv->io_base + _REG(VENC_VDAC_DACSEL0));

	if (meson_vpu_is_compatible(priv, "amlogic,meson-gxbb-vpu"))
		regmap_write(priv->hhi, HHI_VDAC_CNTL0, 1);
	else if (meson_vpu_is_compatible(priv, "amlogic,meson-gxm-vpu") ||
		 meson_vpu_is_compatible(priv, "amlogic,meson-gxl-vpu"))
		regmap_write(priv->hhi, HHI_VDAC_CNTL0, 0xf0001);

	regmap_write(priv->hhi, HHI_VDAC_CNTL1, 0);
}