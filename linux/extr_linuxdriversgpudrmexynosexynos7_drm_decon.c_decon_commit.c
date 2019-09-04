#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct exynos_drm_crtc {TYPE_2__ base; struct decon_context* ctx; } ;
struct drm_display_mode {scalar_t__ htotal; scalar_t__ vtotal; int crtc_vsync_end; int crtc_vsync_start; int crtc_vtotal; int crtc_vdisplay; int crtc_hsync_end; int crtc_hsync_start; int crtc_htotal; int crtc_hdisplay; int vdisplay; scalar_t__ hdisplay; } ;
struct decon_context {scalar_t__ regs; int /*<<< orphan*/  i80_if; scalar_t__ suspended; } ;
struct TYPE_3__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 scalar_t__ DECON_UPDATE ; 
 int DECON_UPDATE_STANDALONE_F ; 
 scalar_t__ LINECNT_OP_THRESHOLD ; 
 scalar_t__ VCLKCON1 ; 
 int VCLKCON1_CLKVAL_NUM_VCLK (int) ; 
 scalar_t__ VCLKCON2 ; 
 scalar_t__ VIDCON0 ; 
 int VIDCON0_ENVID ; 
 int VIDCON0_ENVID_F ; 
 scalar_t__ VIDTCON0 ; 
 int VIDTCON0_VBPD (int) ; 
 int VIDTCON0_VFPD (int) ; 
 scalar_t__ VIDTCON1 ; 
 int VIDTCON1_VSPW (int) ; 
 scalar_t__ VIDTCON2 ; 
 int VIDTCON2_HBPD (int) ; 
 int VIDTCON2_HFPD (int) ; 
 scalar_t__ VIDTCON3 ; 
 int VIDTCON3_HSPW (int) ; 
 scalar_t__ VIDTCON4 ; 
 int VIDTCON4_HOZVAL (scalar_t__) ; 
 int VIDTCON4_LINEVAL (int) ; 
 int decon_calc_clkdiv (struct decon_context*,struct drm_display_mode*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void decon_commit(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;
	struct drm_display_mode *mode = &crtc->base.state->adjusted_mode;
	u32 val, clkdiv;

	if (ctx->suspended)
		return;

	/* nothing to do if we haven't set the mode yet */
	if (mode->htotal == 0 || mode->vtotal == 0)
		return;

	if (!ctx->i80_if) {
		int vsync_len, vbpd, vfpd, hsync_len, hbpd, hfpd;
	      /* setup vertical timing values. */
		vsync_len = mode->crtc_vsync_end - mode->crtc_vsync_start;
		vbpd = mode->crtc_vtotal - mode->crtc_vsync_end;
		vfpd = mode->crtc_vsync_start - mode->crtc_vdisplay;

		val = VIDTCON0_VBPD(vbpd - 1) | VIDTCON0_VFPD(vfpd - 1);
		writel(val, ctx->regs + VIDTCON0);

		val = VIDTCON1_VSPW(vsync_len - 1);
		writel(val, ctx->regs + VIDTCON1);

		/* setup horizontal timing values.  */
		hsync_len = mode->crtc_hsync_end - mode->crtc_hsync_start;
		hbpd = mode->crtc_htotal - mode->crtc_hsync_end;
		hfpd = mode->crtc_hsync_start - mode->crtc_hdisplay;

		/* setup horizontal timing values.  */
		val = VIDTCON2_HBPD(hbpd - 1) | VIDTCON2_HFPD(hfpd - 1);
		writel(val, ctx->regs + VIDTCON2);

		val = VIDTCON3_HSPW(hsync_len - 1);
		writel(val, ctx->regs + VIDTCON3);
	}

	/* setup horizontal and vertical display size. */
	val = VIDTCON4_LINEVAL(mode->vdisplay - 1) |
	       VIDTCON4_HOZVAL(mode->hdisplay - 1);
	writel(val, ctx->regs + VIDTCON4);

	writel(mode->vdisplay - 1, ctx->regs + LINECNT_OP_THRESHOLD);

	/*
	 * fields of register with prefix '_F' would be updated
	 * at vsync(same as dma start)
	 */
	val = VIDCON0_ENVID | VIDCON0_ENVID_F;
	writel(val, ctx->regs + VIDCON0);

	clkdiv = decon_calc_clkdiv(ctx, mode);
	if (clkdiv > 1) {
		val = VCLKCON1_CLKVAL_NUM_VCLK(clkdiv - 1);
		writel(val, ctx->regs + VCLKCON1);
		writel(val, ctx->regs + VCLKCON2);
	}

	val = readl(ctx->regs + DECON_UPDATE);
	val |= DECON_UPDATE_STANDALONE_F;
	writel(val, ctx->regs + DECON_UPDATE);
}