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
struct zx_vou_hw {scalar_t__ timing; } ;
struct zx_crtc_bits {int /*<<< orphan*/  tc_enable; } ;
struct zx_crtc {scalar_t__ chnreg; int /*<<< orphan*/  pixclk; struct zx_vou_hw* vou; struct zx_crtc_bits* bits; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHN_CTRL0 ; 
 int /*<<< orphan*/  CHN_ENABLE ; 
 scalar_t__ TIMING_TC_ENABLE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 struct zx_crtc* to_zx_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  zx_writel_mask (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zx_crtc_atomic_disable(struct drm_crtc *crtc,
				   struct drm_crtc_state *old_state)
{
	struct zx_crtc *zcrtc = to_zx_crtc(crtc);
	const struct zx_crtc_bits *bits = zcrtc->bits;
	struct zx_vou_hw *vou = zcrtc->vou;

	clk_disable_unprepare(zcrtc->pixclk);

	drm_crtc_vblank_off(crtc);

	/* Disable channel */
	zx_writel_mask(zcrtc->chnreg + CHN_CTRL0, CHN_ENABLE, 0);

	/* Disable TIMING_CTRL */
	zx_writel_mask(vou->timing + TIMING_TC_ENABLE, bits->tc_enable, 0);
}