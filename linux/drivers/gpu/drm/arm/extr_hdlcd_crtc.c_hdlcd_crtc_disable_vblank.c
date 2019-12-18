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
 unsigned int HDLCD_INTERRUPT_VSYNC ; 
 int /*<<< orphan*/  HDLCD_REG_INT_MASK ; 
 struct hdlcd_drm_private* crtc_to_hdlcd_priv (struct drm_crtc*) ; 
 unsigned int hdlcd_read (struct hdlcd_drm_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdlcd_write (struct hdlcd_drm_private*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hdlcd_crtc_disable_vblank(struct drm_crtc *crtc)
{
	struct hdlcd_drm_private *hdlcd = crtc_to_hdlcd_priv(crtc);
	unsigned int mask = hdlcd_read(hdlcd, HDLCD_REG_INT_MASK);

	hdlcd_write(hdlcd, HDLCD_REG_INT_MASK, mask & ~HDLCD_INTERRUPT_VSYNC);
}