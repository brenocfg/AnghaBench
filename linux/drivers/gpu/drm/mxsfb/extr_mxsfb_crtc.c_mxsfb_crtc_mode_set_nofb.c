#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int bus_flags; } ;
struct TYPE_11__ {TYPE_4__ display_info; } ;
struct TYPE_8__ {TYPE_1__* state; } ;
struct TYPE_9__ {TYPE_2__ crtc; } ;
struct mxsfb_drm_private {scalar_t__ base; TYPE_6__* devdata; int /*<<< orphan*/  clk; TYPE_5__ connector; TYPE_3__ pipe; } ;
struct drm_display_mode {int crtc_clock; int crtc_vsync_end; int crtc_vsync_start; int flags; int crtc_vtotal; int crtc_hsync_end; int crtc_hsync_start; int crtc_htotal; int /*<<< orphan*/  hdisplay; int /*<<< orphan*/  crtc_hdisplay; int /*<<< orphan*/  crtc_vdisplay; } ;
struct TYPE_12__ {scalar_t__ transfer_count; } ;
struct TYPE_7__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int CTRL1_FIFO_CLEAR ; 
 int const DRM_BUS_FLAG_DE_LOW ; 
 int const DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 scalar_t__ LCDC_CTRL1 ; 
 scalar_t__ LCDC_VDCTRL0 ; 
 scalar_t__ LCDC_VDCTRL1 ; 
 scalar_t__ LCDC_VDCTRL2 ; 
 scalar_t__ LCDC_VDCTRL3 ; 
 scalar_t__ LCDC_VDCTRL4 ; 
 scalar_t__ REG_SET ; 
 int SET_DOTCLK_H_VALID_DATA_CNT (int /*<<< orphan*/ ) ; 
 int SET_HOR_WAIT_CNT (int) ; 
 int SET_VERT_WAIT_CNT (int) ; 
 int TRANSFER_COUNT_SET_HCOUNT (int /*<<< orphan*/ ) ; 
 int TRANSFER_COUNT_SET_VCOUNT (int /*<<< orphan*/ ) ; 
 int VDCTRL0_DOTCLK_ACT_FALLING ; 
 int VDCTRL0_ENABLE_ACT_HIGH ; 
 int VDCTRL0_ENABLE_PRESENT ; 
 int VDCTRL0_HSYNC_ACT_HIGH ; 
 int VDCTRL0_SET_VSYNC_PULSE_WIDTH (int) ; 
 int VDCTRL0_VSYNC_ACT_HIGH ; 
 int VDCTRL0_VSYNC_PERIOD_UNIT ; 
 int VDCTRL0_VSYNC_PULSE_WIDTH_UNIT ; 
 int VDCTRL2_SET_HSYNC_PERIOD (int) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int mxsfb_reset_block (scalar_t__) ; 
 int /*<<< orphan*/  mxsfb_set_bus_fmt (struct mxsfb_drm_private*) ; 
 int mxsfb_set_pixel_fmt (struct mxsfb_drm_private*) ; 
 int set_hsync_pulse_width (struct mxsfb_drm_private*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxsfb_crtc_mode_set_nofb(struct mxsfb_drm_private *mxsfb)
{
	struct drm_display_mode *m = &mxsfb->pipe.crtc.state->adjusted_mode;
	const u32 bus_flags = mxsfb->connector.display_info.bus_flags;
	u32 vdctrl0, vsync_pulse_len, hsync_pulse_len;
	int err;

	/*
	 * It seems, you can't re-program the controller if it is still
	 * running. This may lead to shifted pictures (FIFO issue?), so
	 * first stop the controller and drain its FIFOs.
	 */

	/* Mandatory eLCDIF reset as per the Reference Manual */
	err = mxsfb_reset_block(mxsfb->base);
	if (err)
		return;

	/* Clear the FIFOs */
	writel(CTRL1_FIFO_CLEAR, mxsfb->base + LCDC_CTRL1 + REG_SET);

	err = mxsfb_set_pixel_fmt(mxsfb);
	if (err)
		return;

	clk_set_rate(mxsfb->clk, m->crtc_clock * 1000);

	writel(TRANSFER_COUNT_SET_VCOUNT(m->crtc_vdisplay) |
	       TRANSFER_COUNT_SET_HCOUNT(m->crtc_hdisplay),
	       mxsfb->base + mxsfb->devdata->transfer_count);

	vsync_pulse_len = m->crtc_vsync_end - m->crtc_vsync_start;

	vdctrl0 = VDCTRL0_ENABLE_PRESENT |	/* Always in DOTCLOCK mode */
		  VDCTRL0_VSYNC_PERIOD_UNIT |
		  VDCTRL0_VSYNC_PULSE_WIDTH_UNIT |
		  VDCTRL0_SET_VSYNC_PULSE_WIDTH(vsync_pulse_len);
	if (m->flags & DRM_MODE_FLAG_PHSYNC)
		vdctrl0 |= VDCTRL0_HSYNC_ACT_HIGH;
	if (m->flags & DRM_MODE_FLAG_PVSYNC)
		vdctrl0 |= VDCTRL0_VSYNC_ACT_HIGH;
	/* Make sure Data Enable is high active by default */
	if (!(bus_flags & DRM_BUS_FLAG_DE_LOW))
		vdctrl0 |= VDCTRL0_ENABLE_ACT_HIGH;
	/*
	 * DRM_BUS_FLAG_PIXDATA_DRIVE_ defines are controller centric,
	 * controllers VDCTRL0_DOTCLK is display centric.
	 * Drive on positive edge       -> display samples on falling edge
	 * DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE -> VDCTRL0_DOTCLK_ACT_FALLING
	 */
	if (bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE)
		vdctrl0 |= VDCTRL0_DOTCLK_ACT_FALLING;

	writel(vdctrl0, mxsfb->base + LCDC_VDCTRL0);

	mxsfb_set_bus_fmt(mxsfb);

	/* Frame length in lines. */
	writel(m->crtc_vtotal, mxsfb->base + LCDC_VDCTRL1);

	/* Line length in units of clocks or pixels. */
	hsync_pulse_len = m->crtc_hsync_end - m->crtc_hsync_start;
	writel(set_hsync_pulse_width(mxsfb, hsync_pulse_len) |
	       VDCTRL2_SET_HSYNC_PERIOD(m->crtc_htotal),
	       mxsfb->base + LCDC_VDCTRL2);

	writel(SET_HOR_WAIT_CNT(m->crtc_htotal - m->crtc_hsync_start) |
	       SET_VERT_WAIT_CNT(m->crtc_vtotal - m->crtc_vsync_start),
	       mxsfb->base + LCDC_VDCTRL3);

	writel(SET_DOTCLK_H_VALID_DATA_CNT(m->hdisplay),
	       mxsfb->base + LCDC_VDCTRL4);
}