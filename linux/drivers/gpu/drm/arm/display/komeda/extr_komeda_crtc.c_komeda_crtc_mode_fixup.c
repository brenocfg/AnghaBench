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
struct komeda_crtc {TYPE_1__* master; } ;
struct drm_display_mode {int crtc_clock; int crtc_hdisplay; int crtc_hsync_start; int crtc_hsync_end; int crtc_htotal; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pxlclk; scalar_t__ dual_link; } ;

/* Variables and functions */
 int clk_round_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 struct komeda_crtc* to_kcrtc (struct drm_crtc*) ; 

__attribute__((used)) static bool komeda_crtc_mode_fixup(struct drm_crtc *crtc,
				   const struct drm_display_mode *m,
				   struct drm_display_mode *adjusted_mode)
{
	struct komeda_crtc *kcrtc = to_kcrtc(crtc);
	unsigned long clk_rate;

	drm_mode_set_crtcinfo(adjusted_mode, 0);
	/* In dual link half the horizontal settings */
	if (kcrtc->master->dual_link) {
		adjusted_mode->crtc_clock /= 2;
		adjusted_mode->crtc_hdisplay /= 2;
		adjusted_mode->crtc_hsync_start /= 2;
		adjusted_mode->crtc_hsync_end /= 2;
		adjusted_mode->crtc_htotal /= 2;
	}

	clk_rate = adjusted_mode->crtc_clock * 1000;
	/* crtc_clock will be used as the komeda output pixel clock */
	adjusted_mode->crtc_clock = clk_round_rate(kcrtc->master->pxlclk,
						   clk_rate) / 1000;

	return true;
}