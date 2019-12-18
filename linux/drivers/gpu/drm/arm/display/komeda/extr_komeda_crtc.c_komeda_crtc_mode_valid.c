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
struct komeda_pipeline {int /*<<< orphan*/  pxlclk; scalar_t__ dual_link; } ;
struct komeda_dev {int /*<<< orphan*/  aclk; } ;
struct komeda_crtc {struct komeda_pipeline* master; } ;
struct drm_display_mode {int flags; int clock; int /*<<< orphan*/  name; } ;
struct drm_crtc {TYPE_1__* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {struct komeda_dev* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,unsigned long,...) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_NOCLOCK ; 
 int MODE_NO_INTERLACE ; 
 int MODE_OK ; 
 unsigned long clk_round_rate (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long komeda_calc_min_aclk_rate (struct komeda_crtc*,unsigned long) ; 
 struct komeda_crtc* to_kcrtc (struct drm_crtc*) ; 

__attribute__((used)) static enum drm_mode_status
komeda_crtc_mode_valid(struct drm_crtc *crtc, const struct drm_display_mode *m)
{
	struct komeda_dev *mdev = crtc->dev->dev_private;
	struct komeda_crtc *kcrtc = to_kcrtc(crtc);
	struct komeda_pipeline *master = kcrtc->master;
	unsigned long min_pxlclk, min_aclk;

	if (m->flags & DRM_MODE_FLAG_INTERLACE)
		return MODE_NO_INTERLACE;

	min_pxlclk = m->clock * 1000;
	if (master->dual_link)
		min_pxlclk /= 2;

	if (min_pxlclk != clk_round_rate(master->pxlclk, min_pxlclk)) {
		DRM_DEBUG_ATOMIC("pxlclk doesn't support %lu Hz\n", min_pxlclk);

		return MODE_NOCLOCK;
	}

	min_aclk = komeda_calc_min_aclk_rate(to_kcrtc(crtc), min_pxlclk);
	if (clk_round_rate(mdev->aclk, min_aclk) < min_aclk) {
		DRM_DEBUG_ATOMIC("engine clk can't satisfy the requirement of %s-clk: %lu.\n",
				 m->name, min_pxlclk);

		return MODE_CLOCK_HIGH;
	}

	return MODE_OK;
}