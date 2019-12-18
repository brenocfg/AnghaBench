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
struct hdlcd_drm_private {int /*<<< orphan*/  clk; } ;
struct drm_display_mode {int clock; } ;
struct drm_crtc {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int MODE_NOCLOCK ; 
 int MODE_OK ; 
 int abs (long) ; 
 long clk_round_rate (int /*<<< orphan*/ ,long) ; 
 struct hdlcd_drm_private* crtc_to_hdlcd_priv (struct drm_crtc*) ; 

__attribute__((used)) static enum drm_mode_status hdlcd_crtc_mode_valid(struct drm_crtc *crtc,
		const struct drm_display_mode *mode)
{
	struct hdlcd_drm_private *hdlcd = crtc_to_hdlcd_priv(crtc);
	long rate, clk_rate = mode->clock * 1000;

	rate = clk_round_rate(hdlcd->clk, clk_rate);
	/* 0.1% seems a close enough tolerance for the TDA19988 on Juno */
	if (abs(rate - clk_rate) * 1000 > clk_rate) {
		/* clock required by mode not supported by hardware */
		return MODE_NOCLOCK;
	}

	return MODE_OK;
}