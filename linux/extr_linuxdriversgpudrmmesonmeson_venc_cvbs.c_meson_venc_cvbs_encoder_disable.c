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
struct meson_drm {int /*<<< orphan*/  hhi; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HHI_VDAC_CNTL0 ; 
 int /*<<< orphan*/  HHI_VDAC_CNTL1 ; 
 struct meson_venc_cvbs* encoder_to_meson_venc_cvbs (struct drm_encoder*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void meson_venc_cvbs_encoder_disable(struct drm_encoder *encoder)
{
	struct meson_venc_cvbs *meson_venc_cvbs =
					encoder_to_meson_venc_cvbs(encoder);
	struct meson_drm *priv = meson_venc_cvbs->priv;

	/* Disable CVBS VDAC */
	regmap_write(priv->hhi, HHI_VDAC_CNTL0, 0);
	regmap_write(priv->hhi, HHI_VDAC_CNTL1, 8);
}