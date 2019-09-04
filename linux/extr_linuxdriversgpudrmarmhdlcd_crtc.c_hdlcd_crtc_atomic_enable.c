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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDLCD_REG_COMMAND ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct hdlcd_drm_private* crtc_to_hdlcd_priv (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  hdlcd_crtc_mode_set_nofb (struct drm_crtc*) ; 
 int /*<<< orphan*/  hdlcd_write (struct hdlcd_drm_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdlcd_crtc_atomic_enable(struct drm_crtc *crtc,
				     struct drm_crtc_state *old_state)
{
	struct hdlcd_drm_private *hdlcd = crtc_to_hdlcd_priv(crtc);

	clk_prepare_enable(hdlcd->clk);
	hdlcd_crtc_mode_set_nofb(crtc);
	hdlcd_write(hdlcd, HDLCD_REG_COMMAND, 1);
	drm_crtc_vblank_on(crtc);
}