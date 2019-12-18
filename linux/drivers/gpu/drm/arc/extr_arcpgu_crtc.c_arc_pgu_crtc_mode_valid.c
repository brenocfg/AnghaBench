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
struct drm_display_mode {int clock; } ;
struct drm_crtc {int dummy; } ;
struct arcpgu_drm_private {int /*<<< orphan*/  clk; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_NOCLOCK ; 
 int MODE_OK ; 
 long clk_round_rate (int /*<<< orphan*/ ,long) ; 
 struct arcpgu_drm_private* crtc_to_arcpgu_priv (struct drm_crtc*) ; 
 long max (long,long) ; 
 long min (long,long) ; 

__attribute__((used)) static enum drm_mode_status arc_pgu_crtc_mode_valid(struct drm_crtc *crtc,
						    const struct drm_display_mode *mode)
{
	struct arcpgu_drm_private *arcpgu = crtc_to_arcpgu_priv(crtc);
	long rate, clk_rate = mode->clock * 1000;
	long diff = clk_rate / 200; /* +-0.5% allowed by HDMI spec */

	rate = clk_round_rate(arcpgu->clk, clk_rate);
	if ((max(rate, clk_rate) - min(rate, clk_rate) < diff) && (rate > 0))
		return MODE_OK;

	return MODE_NOCLOCK;
}