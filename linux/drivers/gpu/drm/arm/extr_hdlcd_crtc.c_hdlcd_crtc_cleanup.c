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
struct hdlcd_drm_private {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDLCD_REG_COMMAND ; 
 struct hdlcd_drm_private* crtc_to_hdlcd_priv (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  hdlcd_write (struct hdlcd_drm_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdlcd_crtc_cleanup(struct drm_crtc *crtc)
{
	struct hdlcd_drm_private *hdlcd = crtc_to_hdlcd_priv(crtc);

	/* stop the controller on cleanup */
	hdlcd_write(hdlcd, HDLCD_REG_COMMAND, 0);
	drm_crtc_cleanup(crtc);
}