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
struct drm_crtc_state {struct drm_display_mode adjusted_mode; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 long clk_round_rate (int /*<<< orphan*/ ,long) ; 
 struct hdlcd_drm_private* crtc_to_hdlcd_priv (struct drm_crtc*) ; 

__attribute__((used)) static int hdlcd_crtc_atomic_check(struct drm_crtc *crtc,
				   struct drm_crtc_state *state)
{
	struct hdlcd_drm_private *hdlcd = crtc_to_hdlcd_priv(crtc);
	struct drm_display_mode *mode = &state->adjusted_mode;
	long rate, clk_rate = mode->clock * 1000;

	rate = clk_round_rate(hdlcd->clk, clk_rate);
	if (rate != clk_rate) {
		/* clock required by mode not supported by hardware */
		return -EINVAL;
	}

	return 0;
}