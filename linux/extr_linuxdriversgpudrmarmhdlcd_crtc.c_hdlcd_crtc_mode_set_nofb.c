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
struct videomode {int vfront_porch; int vback_porch; int vsync_len; int hfront_porch; int hback_porch; int hsync_len; } ;
struct hdlcd_drm_private {int /*<<< orphan*/  clk; } ;
struct drm_display_mode {int crtc_vsync_start; int crtc_vdisplay; int crtc_vtotal; int crtc_vsync_end; int crtc_hsync_start; int crtc_hdisplay; int crtc_htotal; int crtc_hsync_end; int flags; int crtc_clock; } ;
struct drm_crtc {TYPE_1__* state; } ;
struct TYPE_2__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 unsigned int HDLCD_BUS_BURST_16 ; 
 unsigned int HDLCD_BUS_MAX_OUTSTAND ; 
 unsigned int HDLCD_POLARITY_DATA ; 
 unsigned int HDLCD_POLARITY_DATAEN ; 
 unsigned int HDLCD_POLARITY_HSYNC ; 
 unsigned int HDLCD_POLARITY_VSYNC ; 
 int /*<<< orphan*/  HDLCD_REG_BUS_OPTIONS ; 
 int /*<<< orphan*/  HDLCD_REG_H_BACK_PORCH ; 
 int /*<<< orphan*/  HDLCD_REG_H_DATA ; 
 int /*<<< orphan*/  HDLCD_REG_H_FRONT_PORCH ; 
 int /*<<< orphan*/  HDLCD_REG_H_SYNC ; 
 int /*<<< orphan*/  HDLCD_REG_POLARITIES ; 
 int /*<<< orphan*/  HDLCD_REG_V_BACK_PORCH ; 
 int /*<<< orphan*/  HDLCD_REG_V_DATA ; 
 int /*<<< orphan*/  HDLCD_REG_V_FRONT_PORCH ; 
 int /*<<< orphan*/  HDLCD_REG_V_SYNC ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct hdlcd_drm_private* crtc_to_hdlcd_priv (struct drm_crtc*) ; 
 unsigned int hdlcd_set_pxl_fmt (struct drm_crtc*) ; 
 int /*<<< orphan*/  hdlcd_write (struct hdlcd_drm_private*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void hdlcd_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct hdlcd_drm_private *hdlcd = crtc_to_hdlcd_priv(crtc);
	struct drm_display_mode *m = &crtc->state->adjusted_mode;
	struct videomode vm;
	unsigned int polarities, err;

	vm.vfront_porch = m->crtc_vsync_start - m->crtc_vdisplay;
	vm.vback_porch = m->crtc_vtotal - m->crtc_vsync_end;
	vm.vsync_len = m->crtc_vsync_end - m->crtc_vsync_start;
	vm.hfront_porch = m->crtc_hsync_start - m->crtc_hdisplay;
	vm.hback_porch = m->crtc_htotal - m->crtc_hsync_end;
	vm.hsync_len = m->crtc_hsync_end - m->crtc_hsync_start;

	polarities = HDLCD_POLARITY_DATAEN | HDLCD_POLARITY_DATA;

	if (m->flags & DRM_MODE_FLAG_PHSYNC)
		polarities |= HDLCD_POLARITY_HSYNC;
	if (m->flags & DRM_MODE_FLAG_PVSYNC)
		polarities |= HDLCD_POLARITY_VSYNC;

	/* Allow max number of outstanding requests and largest burst size */
	hdlcd_write(hdlcd, HDLCD_REG_BUS_OPTIONS,
		    HDLCD_BUS_MAX_OUTSTAND | HDLCD_BUS_BURST_16);

	hdlcd_write(hdlcd, HDLCD_REG_V_DATA, m->crtc_vdisplay - 1);
	hdlcd_write(hdlcd, HDLCD_REG_V_BACK_PORCH, vm.vback_porch - 1);
	hdlcd_write(hdlcd, HDLCD_REG_V_FRONT_PORCH, vm.vfront_porch - 1);
	hdlcd_write(hdlcd, HDLCD_REG_V_SYNC, vm.vsync_len - 1);
	hdlcd_write(hdlcd, HDLCD_REG_H_DATA, m->crtc_hdisplay - 1);
	hdlcd_write(hdlcd, HDLCD_REG_H_BACK_PORCH, vm.hback_porch - 1);
	hdlcd_write(hdlcd, HDLCD_REG_H_FRONT_PORCH, vm.hfront_porch - 1);
	hdlcd_write(hdlcd, HDLCD_REG_H_SYNC, vm.hsync_len - 1);
	hdlcd_write(hdlcd, HDLCD_REG_POLARITIES, polarities);

	err = hdlcd_set_pxl_fmt(crtc);
	if (err)
		return;

	clk_set_rate(hdlcd->clk, m->crtc_clock * 1000);
}