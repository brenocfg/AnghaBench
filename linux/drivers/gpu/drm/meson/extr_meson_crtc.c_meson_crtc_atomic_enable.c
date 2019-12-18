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
struct TYPE_2__ {int /*<<< orphan*/  hdisplay; } ;
struct drm_crtc_state {TYPE_1__ mode; } ;
struct drm_crtc {struct drm_crtc_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPP_MISC ; 
 int /*<<< orphan*/  VPP_POSTBLEND_ENABLE ; 
 int /*<<< orphan*/  VPP_POSTBLEND_H_SIZE ; 
 int /*<<< orphan*/  VPP_PREBLEND_VD1_V_START_END ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 struct meson_crtc* to_meson_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_crtc_atomic_enable(struct drm_crtc *crtc,
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

	/* Enable VPP Postblend */
	writel(crtc_state->mode.hdisplay,
	       priv->io_base + _REG(VPP_POSTBLEND_H_SIZE));

	/* VD1 Preblend vertical start/end */
	writel(FIELD_PREP(GENMASK(11, 0), 2303),
			priv->io_base + _REG(VPP_PREBLEND_VD1_V_START_END));

	writel_bits_relaxed(VPP_POSTBLEND_ENABLE, VPP_POSTBLEND_ENABLE,
			    priv->io_base + _REG(VPP_MISC));

	drm_crtc_vblank_on(crtc);
}