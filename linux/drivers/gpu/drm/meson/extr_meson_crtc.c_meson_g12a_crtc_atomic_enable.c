#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct meson_drm {scalar_t__ io_base; } ;
struct meson_crtc {struct meson_drm* priv; } ;
struct TYPE_2__ {int hdisplay; int vdisplay; } ;
struct drm_crtc_state {TYPE_1__ mode; } ;
struct drm_crtc {struct drm_crtc_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPP_OSD1_BLD_H_SCOPE ; 
 int /*<<< orphan*/  VPP_OSD1_BLD_V_SCOPE ; 
 int /*<<< orphan*/  VPP_OUT_H_V_SIZE ; 
 int /*<<< orphan*/  VPP_POSTBLEND_H_SIZE ; 
 int /*<<< orphan*/  VPP_PREBLEND_VD1_V_START_END ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 struct meson_crtc* to_meson_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void meson_g12a_crtc_atomic_enable(struct drm_crtc *crtc,
					  struct drm_crtc_state *old_state)
{
	struct meson_crtc *meson_crtc = to_meson_crtc(crtc);
	struct drm_crtc_state *crtc_state = crtc->state;
	struct meson_drm *priv = meson_crtc->priv;

	DRM_DEBUG_DRIVER("\n");

	if (!crtc_state) {
		DRM_ERROR("Invalid crtc_state\n");
		return;
	}

	/* VD1 Preblend vertical start/end */
	writel(FIELD_PREP(GENMASK(11, 0), 2303),
	       priv->io_base + _REG(VPP_PREBLEND_VD1_V_START_END));

	/* Setup Blender */
	writel(crtc_state->mode.hdisplay |
	       crtc_state->mode.vdisplay << 16,
	       priv->io_base + _REG(VPP_POSTBLEND_H_SIZE));

	writel_relaxed(0 << 16 |
			(crtc_state->mode.hdisplay - 1),
			priv->io_base + _REG(VPP_OSD1_BLD_H_SCOPE));
	writel_relaxed(0 << 16 |
			(crtc_state->mode.vdisplay - 1),
			priv->io_base + _REG(VPP_OSD1_BLD_V_SCOPE));
	writel_relaxed(crtc_state->mode.hdisplay << 16 |
			crtc_state->mode.vdisplay,
			priv->io_base + _REG(VPP_OUT_H_V_SIZE));

	drm_crtc_vblank_on(crtc);
}