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
typedef  int u32 ;
struct sti_vid {scalar_t__ regs; } ;
struct drm_plane_state {int crtc_x; int crtc_y; int src_h; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; struct drm_crtc* crtc; } ;
struct drm_display_mode {scalar_t__ vdisplay; scalar_t__ hdisplay; } ;
struct drm_crtc {struct drm_display_mode mode; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 scalar_t__ VID_CTL ; 
 int VID_CTL_IGNORE ; 
 int VID_MIN_HD_HEIGHT ; 
 scalar_t__ VID_MPR0 ; 
 int VID_MPR0_BT601 ; 
 int VID_MPR0_BT709 ; 
 scalar_t__ VID_MPR1 ; 
 int VID_MPR1_BT601 ; 
 int VID_MPR1_BT709 ; 
 scalar_t__ VID_MPR2 ; 
 int VID_MPR2_BT601 ; 
 int VID_MPR2_BT709 ; 
 scalar_t__ VID_MPR3 ; 
 int VID_MPR3_BT601 ; 
 int VID_MPR3_BT709 ; 
 scalar_t__ VID_VPO ; 
 scalar_t__ VID_VPS ; 
 int clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int readl (scalar_t__) ; 
 int sti_vtg_get_line_number (struct drm_display_mode,int) ; 
 int sti_vtg_get_pixel_number (struct drm_display_mode,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void sti_vid_commit(struct sti_vid *vid,
		    struct drm_plane_state *state)
{
	struct drm_crtc *crtc = state->crtc;
	struct drm_display_mode *mode = &crtc->mode;
	int dst_x = state->crtc_x;
	int dst_y = state->crtc_y;
	int dst_w = clamp_val(state->crtc_w, 0, mode->hdisplay - dst_x);
	int dst_h = clamp_val(state->crtc_h, 0, mode->vdisplay - dst_y);
	int src_h = state->src_h >> 16;
	u32 val, ydo, xdo, yds, xds;

	/* Input / output size
	 * Align to upper even value */
	dst_w = ALIGN(dst_w, 2);
	dst_h = ALIGN(dst_h, 2);

	/* Unmask */
	val = readl(vid->regs + VID_CTL);
	val &= ~VID_CTL_IGNORE;
	writel(val, vid->regs + VID_CTL);

	ydo = sti_vtg_get_line_number(*mode, dst_y);
	yds = sti_vtg_get_line_number(*mode, dst_y + dst_h - 1);
	xdo = sti_vtg_get_pixel_number(*mode, dst_x);
	xds = sti_vtg_get_pixel_number(*mode, dst_x + dst_w - 1);

	writel((ydo << 16) | xdo, vid->regs + VID_VPO);
	writel((yds << 16) | xds, vid->regs + VID_VPS);

	/* Color conversion parameters */
	if (src_h >= VID_MIN_HD_HEIGHT) {
		writel(VID_MPR0_BT709, vid->regs + VID_MPR0);
		writel(VID_MPR1_BT709, vid->regs + VID_MPR1);
		writel(VID_MPR2_BT709, vid->regs + VID_MPR2);
		writel(VID_MPR3_BT709, vid->regs + VID_MPR3);
	} else {
		writel(VID_MPR0_BT601, vid->regs + VID_MPR0);
		writel(VID_MPR1_BT601, vid->regs + VID_MPR1);
		writel(VID_MPR2_BT601, vid->regs + VID_MPR2);
		writel(VID_MPR3_BT601, vid->regs + VID_MPR3);
	}
}