#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int* pix_fmt_hw; int bus_width; scalar_t__ non_alpha_only_l1; } ;
struct ltdc_device {int error_status; int /*<<< orphan*/  err_lock; TYPE_5__* plane_fpsi; int /*<<< orphan*/  regs; TYPE_3__ caps; } ;
struct drm_plane_state {int crtc_x; int crtc_w; int crtc_y; int crtc_h; int src_x; int src_y; int src_w; int src_h; int /*<<< orphan*/  crtc; struct drm_framebuffer* fb; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int index; scalar_t__ type; TYPE_1__ base; struct drm_plane_state* state; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {int* pitches; TYPE_4__* format; TYPE_2__ base; } ;
typedef  enum ltdc_pix_fmt { ____Placeholder_ltdc_pix_fmt } ltdc_pix_fmt ;
struct TYPE_10__ {int /*<<< orphan*/  counter; } ;
struct TYPE_9__ {scalar_t__ format; int* cpp; int /*<<< orphan*/  has_alpha; } ;

/* Variables and functions */
 int BF1_CA ; 
 int BF1_PAXCA ; 
 int BF2_1CA ; 
 int BF2_1PAXCA ; 
 int BPCR_AHBP ; 
 int BPCR_AVBP ; 
 int CONSTA_MAX ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,char*) ; 
 scalar_t__ DRM_FORMAT_C8 ; 
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int ISR_FUIF ; 
 int ISR_TERRIF ; 
 int LAY_OFS ; 
 int /*<<< orphan*/  LTDC_BPCR ; 
 int LTDC_L1BFCR ; 
 int LTDC_L1CACR ; 
 int LTDC_L1CFBAR ; 
 int LTDC_L1CFBLNR ; 
 int LTDC_L1CFBLR ; 
 int LTDC_L1CR ; 
 int LTDC_L1PFCR ; 
 int LTDC_L1WHPCR ; 
 int LTDC_L1WVPCR ; 
 int LXBFCR_BF1 ; 
 int LXBFCR_BF2 ; 
 int LXCACR_CONSTA ; 
 int LXCFBLNR_CFBLN ; 
 int LXCFBLR_CFBLL ; 
 int LXCFBLR_CFBP ; 
 int LXCR_CLUTEN ; 
 int LXCR_LEN ; 
 int LXPFCR_PF ; 
 int LXWHPCR_WHSPPOS ; 
 int LXWHPCR_WHSTPOS ; 
 int LXWVPCR_WVSPPOS ; 
 int LXWVPCR_WVSTPOS ; 
 int NB_PF ; 
 scalar_t__ drm_fb_cma_get_gem_addr (struct drm_framebuffer*,struct drm_plane_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ltdc_device* plane_to_ltdc (struct drm_plane*) ; 
 int reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ ,int,int) ; 
 int to_ltdc_pixelformat (scalar_t__) ; 

__attribute__((used)) static void ltdc_plane_atomic_update(struct drm_plane *plane,
				     struct drm_plane_state *oldstate)
{
	struct ltdc_device *ldev = plane_to_ltdc(plane);
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = state->fb;
	u32 lofs = plane->index * LAY_OFS;
	u32 x0 = state->crtc_x;
	u32 x1 = state->crtc_x + state->crtc_w - 1;
	u32 y0 = state->crtc_y;
	u32 y1 = state->crtc_y + state->crtc_h - 1;
	u32 src_x, src_y, src_w, src_h;
	u32 val, pitch_in_bytes, line_length, paddr, ahbp, avbp, bpcr;
	enum ltdc_pix_fmt pf;

	if (!state->crtc || !fb) {
		DRM_DEBUG_DRIVER("fb or crtc NULL");
		return;
	}

	/* convert src_ from 16:16 format */
	src_x = state->src_x >> 16;
	src_y = state->src_y >> 16;
	src_w = state->src_w >> 16;
	src_h = state->src_h >> 16;

	DRM_DEBUG_DRIVER("plane:%d fb:%d (%dx%d)@(%d,%d) -> (%dx%d)@(%d,%d)\n",
			 plane->base.id, fb->base.id,
			 src_w, src_h, src_x, src_y,
			 state->crtc_w, state->crtc_h,
			 state->crtc_x, state->crtc_y);

	bpcr = reg_read(ldev->regs, LTDC_BPCR);
	ahbp = (bpcr & BPCR_AHBP) >> 16;
	avbp = bpcr & BPCR_AVBP;

	/* Configures the horizontal start and stop position */
	val = ((x1 + 1 + ahbp) << 16) + (x0 + 1 + ahbp);
	reg_update_bits(ldev->regs, LTDC_L1WHPCR + lofs,
			LXWHPCR_WHSTPOS | LXWHPCR_WHSPPOS, val);

	/* Configures the vertical start and stop position */
	val = ((y1 + 1 + avbp) << 16) + (y0 + 1 + avbp);
	reg_update_bits(ldev->regs, LTDC_L1WVPCR + lofs,
			LXWVPCR_WVSTPOS | LXWVPCR_WVSPPOS, val);

	/* Specifies the pixel format */
	pf = to_ltdc_pixelformat(fb->format->format);
	for (val = 0; val < NB_PF; val++)
		if (ldev->caps.pix_fmt_hw[val] == pf)
			break;

	if (val == NB_PF) {
		DRM_ERROR("Pixel format %.4s not supported\n",
			  (char *)&fb->format->format);
		val = 0;	/* set by default ARGB 32 bits */
	}
	reg_update_bits(ldev->regs, LTDC_L1PFCR + lofs, LXPFCR_PF, val);

	/* Configures the color frame buffer pitch in bytes & line length */
	pitch_in_bytes = fb->pitches[0];
	line_length = fb->format->cpp[0] *
		      (x1 - x0 + 1) + (ldev->caps.bus_width >> 3) - 1;
	val = ((pitch_in_bytes << 16) | line_length);
	reg_update_bits(ldev->regs, LTDC_L1CFBLR + lofs,
			LXCFBLR_CFBLL | LXCFBLR_CFBP, val);

	/* Specifies the constant alpha value */
	val = CONSTA_MAX;
	reg_update_bits(ldev->regs, LTDC_L1CACR + lofs, LXCACR_CONSTA, val);

	/* Specifies the blending factors */
	val = BF1_PAXCA | BF2_1PAXCA;
	if (!fb->format->has_alpha)
		val = BF1_CA | BF2_1CA;

	/* Manage hw-specific capabilities */
	if (ldev->caps.non_alpha_only_l1 &&
	    plane->type != DRM_PLANE_TYPE_PRIMARY)
		val = BF1_PAXCA | BF2_1PAXCA;

	reg_update_bits(ldev->regs, LTDC_L1BFCR + lofs,
			LXBFCR_BF2 | LXBFCR_BF1, val);

	/* Configures the frame buffer line number */
	val = y1 - y0 + 1;
	reg_update_bits(ldev->regs, LTDC_L1CFBLNR + lofs, LXCFBLNR_CFBLN, val);

	/* Sets the FB address */
	paddr = (u32)drm_fb_cma_get_gem_addr(fb, state, 0);

	DRM_DEBUG_DRIVER("fb: phys 0x%08x", paddr);
	reg_write(ldev->regs, LTDC_L1CFBAR + lofs, paddr);

	/* Enable layer and CLUT if needed */
	val = fb->format->format == DRM_FORMAT_C8 ? LXCR_CLUTEN : 0;
	val |= LXCR_LEN;
	reg_update_bits(ldev->regs, LTDC_L1CR + lofs,
			LXCR_LEN | LXCR_CLUTEN, val);

	ldev->plane_fpsi[plane->index].counter++;

	mutex_lock(&ldev->err_lock);
	if (ldev->error_status & ISR_FUIF) {
		DRM_WARN("ltdc fifo underrun: please verify display mode\n");
		ldev->error_status &= ~ISR_FUIF;
	}
	if (ldev->error_status & ISR_TERRIF) {
		DRM_WARN("ltdc transfer error\n");
		ldev->error_status &= ~ISR_TERRIF;
	}
	mutex_unlock(&ldev->err_lock);
}