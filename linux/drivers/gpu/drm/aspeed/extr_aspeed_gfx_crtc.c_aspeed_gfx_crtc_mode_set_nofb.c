#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_display_mode {int crtc_clock; int flags; int hdisplay; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; scalar_t__ vdisplay; scalar_t__ vtotal; int /*<<< orphan*/  hsync_end; scalar_t__ hsync_start; scalar_t__ htotal; } ;
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_6__ {TYPE_2__ crtc; } ;
struct aspeed_gfx {scalar_t__ base; int /*<<< orphan*/  pixel_clk; TYPE_3__ pipe; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 scalar_t__ CRT_CTRL1 ; 
 int CRT_CTRL_HSYNC_NEGATIVE ; 
 int CRT_CTRL_INTERLACED ; 
 int CRT_CTRL_VSYNC_NEGATIVE ; 
 int CRT_DISP_OFFSET (int) ; 
 scalar_t__ CRT_HORIZ0 ; 
 scalar_t__ CRT_HORIZ1 ; 
 int CRT_H_DE (int) ; 
 int CRT_H_RS_END (int /*<<< orphan*/ ) ; 
 int CRT_H_RS_START (scalar_t__) ; 
 int CRT_H_TOTAL (scalar_t__) ; 
 scalar_t__ CRT_OFFSET ; 
 int CRT_TERM_COUNT (int) ; 
 scalar_t__ CRT_THROD ; 
 scalar_t__ CRT_VERT0 ; 
 scalar_t__ CRT_VERT1 ; 
 int CRT_V_DE (scalar_t__) ; 
 int CRT_V_RS_END (int /*<<< orphan*/ ) ; 
 int CRT_V_RS_START (int /*<<< orphan*/ ) ; 
 int CRT_V_TOTAL (scalar_t__) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int G5_CRT_THROD_VAL ; 
 int aspeed_gfx_set_pixel_fmt (struct aspeed_gfx*,int*) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void aspeed_gfx_crtc_mode_set_nofb(struct aspeed_gfx *priv)
{
	struct drm_display_mode *m = &priv->pipe.crtc.state->adjusted_mode;
	u32 ctrl1, d_offset, t_count, bpp;
	int err;

	err = aspeed_gfx_set_pixel_fmt(priv, &bpp);
	if (err)
		return;

#if 0
	/* TODO: we have only been able to test with the 40MHz USB clock. The
	 * clock is fixed, so we cannot adjust it here. */
	clk_set_rate(priv->pixel_clk, m->crtc_clock * 1000);
#endif

	ctrl1 = readl(priv->base + CRT_CTRL1);
	ctrl1 &= ~(CRT_CTRL_INTERLACED |
			CRT_CTRL_HSYNC_NEGATIVE |
			CRT_CTRL_VSYNC_NEGATIVE);

	if (m->flags & DRM_MODE_FLAG_INTERLACE)
		ctrl1 |= CRT_CTRL_INTERLACED;

	if (!(m->flags & DRM_MODE_FLAG_PHSYNC))
		ctrl1 |= CRT_CTRL_HSYNC_NEGATIVE;

	if (!(m->flags & DRM_MODE_FLAG_PVSYNC))
		ctrl1 |= CRT_CTRL_VSYNC_NEGATIVE;

	writel(ctrl1, priv->base + CRT_CTRL1);

	/* Horizontal timing */
	writel(CRT_H_TOTAL(m->htotal - 1) | CRT_H_DE(m->hdisplay - 1),
			priv->base + CRT_HORIZ0);
	writel(CRT_H_RS_START(m->hsync_start - 1) | CRT_H_RS_END(m->hsync_end),
			priv->base + CRT_HORIZ1);


	/* Vertical timing */
	writel(CRT_V_TOTAL(m->vtotal - 1) | CRT_V_DE(m->vdisplay - 1),
			priv->base + CRT_VERT0);
	writel(CRT_V_RS_START(m->vsync_start) | CRT_V_RS_END(m->vsync_end),
			priv->base + CRT_VERT1);

	/*
	 * Display Offset: address difference between consecutive scan lines
	 * Terminal Count: memory size of one scan line
	 */
	d_offset = m->hdisplay * bpp / 8;
	t_count = (m->hdisplay * bpp + 127) / 128;
	writel(CRT_DISP_OFFSET(d_offset) | CRT_TERM_COUNT(t_count),
			priv->base + CRT_OFFSET);

	/*
	 * Threshold: FIFO thresholds of refill and stop (16 byte chunks
	 * per line, rounded up)
	 */
	writel(G5_CRT_THROD_VAL, priv->base + CRT_THROD);
}