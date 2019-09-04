#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct nv17_tv_state {int ptv_200; int ptv_20c; int ptv_304; int ptv_600; int ptv_60c; int ptv_610; int ptv_508; int ptv_614; int ptv_500; int ptv_504; int ptv_604; int ptv_608; int /*<<< orphan*/ * tv_enc; } ;
struct drm_display_mode {int hdisplay; int htotal; int hsync_start; int hsync_end; int flags; scalar_t__ vdisplay; scalar_t__ vsync_end; scalar_t__ vsync_start; scalar_t__ vtotal; } ;
struct TYPE_15__ {int /*<<< orphan*/ * ctv_regs; struct drm_display_mode mode; } ;
struct TYPE_14__ {int vdisplay; int /*<<< orphan*/ * tv_enc; } ;
struct nv17_tv_norm_params {scalar_t__ kind; TYPE_6__ ctv_enc_mode; TYPE_5__ tv_enc_mode; } ;
struct nv04_crtc_reg {int* CRTC; int ramdac_630; int tv_setup; int ramdac_8c0; int* fp_horiz_regs; int fp_control; int fp_debug_0; int fp_margin_color; scalar_t__ fp_debug_2; scalar_t__* fp_vert_regs; int /*<<< orphan*/ * ctv_regs; } ;
struct TYPE_11__ {scalar_t__ family; } ;
struct TYPE_12__ {TYPE_2__ info; } ;
struct TYPE_13__ {TYPE_3__ device; } ;
struct nouveau_drm {TYPE_4__ client; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_18__ {int index; } ;
struct TYPE_10__ {struct nv04_crtc_reg* crtc_reg; } ;
struct TYPE_17__ {TYPE_1__ mode_reg; } ;
struct TYPE_16__ {struct nv17_tv_state state; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 size_t FP_CRTC ; 
 size_t FP_DISPLAY_END ; 
 size_t FP_SYNC_END ; 
 size_t FP_SYNC_START ; 
 size_t FP_TOTAL ; 
 size_t NV_CIO_CRE_53 ; 
 size_t NV_CIO_CRE_54 ; 
 scalar_t__ NV_DEVICE_INFO_V0_RANKINE ; 
 int NV_PRAMDAC_FP_DEBUG_0_XINTERP_BILINEAR ; 
 int NV_PRAMDAC_FP_DEBUG_0_XSCALE_ENABLE ; 
 int NV_PRAMDAC_FP_DEBUG_0_XWEIGHT_ROUND ; 
 int NV_PRAMDAC_FP_DEBUG_0_YINTERP_BILINEAR ; 
 int NV_PRAMDAC_FP_DEBUG_0_YSCALE_ENABLE ; 
 int NV_PRAMDAC_FP_DEBUG_0_YWEIGHT_ROUND ; 
 int NV_PRAMDAC_FP_TG_CONTROL_DISPEN_POS ; 
 int NV_PRAMDAC_FP_TG_CONTROL_HSYNC_POS ; 
 int NV_PRAMDAC_FP_TG_CONTROL_READ_PROG ; 
 int NV_PRAMDAC_FP_TG_CONTROL_VSYNC_POS ; 
 int NV_PRAMDAC_FP_TG_CONTROL_WIDTH_12 ; 
 int NV_RAMDAC_FP_DEBUG_0_TMDS_ENABLED ; 
 scalar_t__ TV_ENC_MODE ; 
 struct nv17_tv_norm_params* get_tv_norm (struct drm_encoder*) ; 
 int max (int,int) ; 
 TYPE_9__* nouveau_crtc (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_8__* nv04_display (struct drm_device*) ; 
 TYPE_7__* to_tv_enc (struct drm_encoder*) ; 

__attribute__((used)) static void nv17_tv_mode_set(struct drm_encoder *encoder,
			     struct drm_display_mode *drm_mode,
			     struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	int head = nouveau_crtc(encoder->crtc)->index;
	struct nv04_crtc_reg *regs = &nv04_display(dev)->mode_reg.crtc_reg[head];
	struct nv17_tv_state *tv_regs = &to_tv_enc(encoder)->state;
	struct nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	int i;

	regs->CRTC[NV_CIO_CRE_53] = 0x40; /* FP_HTIMING */
	regs->CRTC[NV_CIO_CRE_54] = 0; /* FP_VTIMING */
	regs->ramdac_630 = 0x2; /* turn off green mode (tv test pattern?) */
	regs->tv_setup = 1;
	regs->ramdac_8c0 = 0x0;

	if (tv_norm->kind == TV_ENC_MODE) {
		tv_regs->ptv_200 = 0x13111100;
		if (head)
			tv_regs->ptv_200 |= 0x10;

		tv_regs->ptv_20c = 0x808010;
		tv_regs->ptv_304 = 0x2d00000;
		tv_regs->ptv_600 = 0x0;
		tv_regs->ptv_60c = 0x0;
		tv_regs->ptv_610 = 0x1e00000;

		if (tv_norm->tv_enc_mode.vdisplay == 576) {
			tv_regs->ptv_508 = 0x1200000;
			tv_regs->ptv_614 = 0x33;

		} else if (tv_norm->tv_enc_mode.vdisplay == 480) {
			tv_regs->ptv_508 = 0xf00000;
			tv_regs->ptv_614 = 0x13;
		}

		if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE) {
			tv_regs->ptv_500 = 0xe8e0;
			tv_regs->ptv_504 = 0x1710;
			tv_regs->ptv_604 = 0x0;
			tv_regs->ptv_608 = 0x0;
		} else {
			if (tv_norm->tv_enc_mode.vdisplay == 576) {
				tv_regs->ptv_604 = 0x20;
				tv_regs->ptv_608 = 0x10;
				tv_regs->ptv_500 = 0x19710;
				tv_regs->ptv_504 = 0x68f0;

			} else if (tv_norm->tv_enc_mode.vdisplay == 480) {
				tv_regs->ptv_604 = 0x10;
				tv_regs->ptv_608 = 0x20;
				tv_regs->ptv_500 = 0x4b90;
				tv_regs->ptv_504 = 0x1b480;
			}
		}

		for (i = 0; i < 0x40; i++)
			tv_regs->tv_enc[i] = tv_norm->tv_enc_mode.tv_enc[i];

	} else {
		struct drm_display_mode *output_mode =
						&tv_norm->ctv_enc_mode.mode;

		/* The registers in PRAMDAC+0xc00 control some timings and CSC
		 * parameters for the CTV encoder (It's only used for "HD" TV
		 * modes, I don't think I have enough working to guess what
		 * they exactly mean...), it's probably connected at the
		 * output of the FP encoder, but it also needs the analog
		 * encoder in its OR enabled and routed to the head it's
		 * using. It's enabled with the DACCLK register, bits [5:4].
		 */
		for (i = 0; i < 38; i++)
			regs->ctv_regs[i] = tv_norm->ctv_enc_mode.ctv_regs[i];

		regs->fp_horiz_regs[FP_DISPLAY_END] = output_mode->hdisplay - 1;
		regs->fp_horiz_regs[FP_TOTAL] = output_mode->htotal - 1;
		regs->fp_horiz_regs[FP_SYNC_START] =
						output_mode->hsync_start - 1;
		regs->fp_horiz_regs[FP_SYNC_END] = output_mode->hsync_end - 1;
		regs->fp_horiz_regs[FP_CRTC] = output_mode->hdisplay +
			max((output_mode->hdisplay-600)/40 - 1, 1);

		regs->fp_vert_regs[FP_DISPLAY_END] = output_mode->vdisplay - 1;
		regs->fp_vert_regs[FP_TOTAL] = output_mode->vtotal - 1;
		regs->fp_vert_regs[FP_SYNC_START] =
						output_mode->vsync_start - 1;
		regs->fp_vert_regs[FP_SYNC_END] = output_mode->vsync_end - 1;
		regs->fp_vert_regs[FP_CRTC] = output_mode->vdisplay - 1;

		regs->fp_control = NV_PRAMDAC_FP_TG_CONTROL_DISPEN_POS |
			NV_PRAMDAC_FP_TG_CONTROL_READ_PROG |
			NV_PRAMDAC_FP_TG_CONTROL_WIDTH_12;

		if (output_mode->flags & DRM_MODE_FLAG_PVSYNC)
			regs->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_VSYNC_POS;
		if (output_mode->flags & DRM_MODE_FLAG_PHSYNC)
			regs->fp_control |= NV_PRAMDAC_FP_TG_CONTROL_HSYNC_POS;

		regs->fp_debug_0 = NV_PRAMDAC_FP_DEBUG_0_YWEIGHT_ROUND |
			NV_PRAMDAC_FP_DEBUG_0_XWEIGHT_ROUND |
			NV_PRAMDAC_FP_DEBUG_0_YINTERP_BILINEAR |
			NV_PRAMDAC_FP_DEBUG_0_XINTERP_BILINEAR |
			NV_RAMDAC_FP_DEBUG_0_TMDS_ENABLED |
			NV_PRAMDAC_FP_DEBUG_0_YSCALE_ENABLE |
			NV_PRAMDAC_FP_DEBUG_0_XSCALE_ENABLE;

		regs->fp_debug_2 = 0;

		regs->fp_margin_color = 0x801080;

	}
}