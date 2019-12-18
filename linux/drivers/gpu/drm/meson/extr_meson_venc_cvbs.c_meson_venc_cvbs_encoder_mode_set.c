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
struct meson_drm {int dummy; } ;
struct meson_cvbs_mode {int /*<<< orphan*/  enci; int /*<<< orphan*/  mode; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int MESON_CVBS_MODES_COUNT ; 
 int /*<<< orphan*/  MESON_VCLK_CVBS ; 
 int /*<<< orphan*/  MESON_VCLK_TARGET_CVBS ; 
 scalar_t__ drm_mode_equal (struct drm_display_mode*,int /*<<< orphan*/ *) ; 
 struct meson_venc_cvbs* encoder_to_meson_venc_cvbs (struct drm_encoder*) ; 
 struct meson_cvbs_mode* meson_cvbs_modes ; 
 int /*<<< orphan*/  meson_vclk_setup (struct meson_drm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  meson_venci_cvbs_mode_set (struct meson_drm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_venc_cvbs_encoder_mode_set(struct drm_encoder *encoder,
				   struct drm_display_mode *mode,
				   struct drm_display_mode *adjusted_mode)
{
	struct meson_venc_cvbs *meson_venc_cvbs =
					encoder_to_meson_venc_cvbs(encoder);
	struct meson_drm *priv = meson_venc_cvbs->priv;
	int i;

	for (i = 0; i < MESON_CVBS_MODES_COUNT; ++i) {
		struct meson_cvbs_mode *meson_mode = &meson_cvbs_modes[i];

		if (drm_mode_equal(mode, &meson_mode->mode)) {
			meson_venci_cvbs_mode_set(priv,
						  meson_mode->enci);

			/* Setup 27MHz vclk2 for ENCI and VDAC */
			meson_vclk_setup(priv, MESON_VCLK_TARGET_CVBS,
					 MESON_VCLK_CVBS, MESON_VCLK_CVBS,
					 MESON_VCLK_CVBS, true);
			break;
		}
	}
}