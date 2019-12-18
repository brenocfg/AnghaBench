#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct nv04_crtc_reg {int* CRTC; int fb_start; int /*<<< orphan*/  ramdac_gen_ctrl; } ;
struct nouveau_framebuffer {TYPE_4__* nvbo; } ;
struct TYPE_24__ {scalar_t__ family; } ;
struct TYPE_13__ {TYPE_9__ info; } ;
struct TYPE_14__ {TYPE_10__ device; } ;
struct nouveau_drm {TYPE_11__ client; } ;
struct TYPE_21__ {int offset; } ;
struct TYPE_20__ {int depth; } ;
struct nouveau_crtc {size_t index; TYPE_6__ fb; TYPE_5__ lut; } ;
struct drm_framebuffer {int* pitches; TYPE_8__* format; } ;
struct drm_device {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  clock; } ;
struct drm_crtc {TYPE_7__ mode; TYPE_2__* primary; struct drm_device* dev; } ;
struct TYPE_23__ {int depth; int* cpp; } ;
struct TYPE_18__ {int offset; } ;
struct TYPE_19__ {TYPE_3__ bo; } ;
struct TYPE_17__ {struct drm_framebuffer* fb; } ;
struct TYPE_16__ {struct nv04_crtc_reg* crtc_reg; } ;
struct TYPE_15__ {TYPE_1__ mode_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t NV_CIO_CRE_42 ; 
 int /*<<< orphan*/  NV_CIO_CRE_42_OFFSET_11 ; 
 size_t NV_CIO_CRE_47 ; 
 size_t NV_CIO_CRE_FFLWM__INDEX ; 
 size_t NV_CIO_CRE_FF_INDEX ; 
 size_t NV_CIO_CRE_PIXEL_INDEX ; 
 size_t NV_CIO_CRE_RPC0_INDEX ; 
 int /*<<< orphan*/  NV_CIO_CRE_RPC0_OFFSET_10_8 ; 
 size_t NV_CIO_CR_OFFSET_INDEX ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,...) ; 
 scalar_t__ NV_DEVICE_INFO_V0_KELVIN ; 
 int /*<<< orphan*/  NV_PRAMDAC_GENERAL_CONTROL ; 
 int /*<<< orphan*/  NV_PRAMDAC_GENERAL_CONTROL_ALT_MODE_SEL ; 
 void* XLATE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crtc_wr_cio_state (struct drm_crtc*,struct nv04_crtc_reg*,size_t) ; 
 int /*<<< orphan*/  nouveau_calc_arb (struct drm_device*,int /*<<< orphan*/ ,int,int*,int*) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (struct drm_framebuffer*) ; 
 TYPE_12__* nv04_display (struct drm_device*) ; 
 int /*<<< orphan*/  nv_crtc_gamma_load (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv_set_crtc_base (struct drm_device*,size_t,int) ; 

__attribute__((used)) static int
nv04_crtc_do_mode_set_base(struct drm_crtc *crtc,
			   struct drm_framebuffer *passed_fb,
			   int x, int y, bool atomic)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nv04_crtc_reg *regp = &nv04_display(dev)->mode_reg.crtc_reg[nv_crtc->index];
	struct drm_framebuffer *drm_fb;
	struct nouveau_framebuffer *fb;
	int arb_burst, arb_lwm;

	NV_DEBUG(drm, "index %d\n", nv_crtc->index);

	/* no fb bound */
	if (!atomic && !crtc->primary->fb) {
		NV_DEBUG(drm, "No FB bound\n");
		return 0;
	}

	/* If atomic, we want to switch to the fb we were passed, so
	 * now we update pointers to do that.
	 */
	if (atomic) {
		drm_fb = passed_fb;
		fb = nouveau_framebuffer(passed_fb);
	} else {
		drm_fb = crtc->primary->fb;
		fb = nouveau_framebuffer(crtc->primary->fb);
	}

	nv_crtc->fb.offset = fb->nvbo->bo.offset;

	if (nv_crtc->lut.depth != drm_fb->format->depth) {
		nv_crtc->lut.depth = drm_fb->format->depth;
		nv_crtc_gamma_load(crtc);
	}

	/* Update the framebuffer format. */
	regp->CRTC[NV_CIO_CRE_PIXEL_INDEX] &= ~3;
	regp->CRTC[NV_CIO_CRE_PIXEL_INDEX] |= (drm_fb->format->depth + 1) / 8;
	regp->ramdac_gen_ctrl &= ~NV_PRAMDAC_GENERAL_CONTROL_ALT_MODE_SEL;
	if (drm_fb->format->depth == 16)
		regp->ramdac_gen_ctrl |= NV_PRAMDAC_GENERAL_CONTROL_ALT_MODE_SEL;
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_PIXEL_INDEX);
	NVWriteRAMDAC(dev, nv_crtc->index, NV_PRAMDAC_GENERAL_CONTROL,
		      regp->ramdac_gen_ctrl);

	regp->CRTC[NV_CIO_CR_OFFSET_INDEX] = drm_fb->pitches[0] >> 3;
	regp->CRTC[NV_CIO_CRE_RPC0_INDEX] =
		XLATE(drm_fb->pitches[0] >> 3, 8, NV_CIO_CRE_RPC0_OFFSET_10_8);
	regp->CRTC[NV_CIO_CRE_42] =
		XLATE(drm_fb->pitches[0] / 8, 11, NV_CIO_CRE_42_OFFSET_11);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_RPC0_INDEX);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CR_OFFSET_INDEX);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_42);

	/* Update the framebuffer location. */
	regp->fb_start = nv_crtc->fb.offset & ~3;
	regp->fb_start += (y * drm_fb->pitches[0]) + (x * drm_fb->format->cpp[0]);
	nv_set_crtc_base(dev, nv_crtc->index, regp->fb_start);

	/* Update the arbitration parameters. */
	nouveau_calc_arb(dev, crtc->mode.clock, drm_fb->format->cpp[0] * 8,
			 &arb_burst, &arb_lwm);

	regp->CRTC[NV_CIO_CRE_FF_INDEX] = arb_burst;
	regp->CRTC[NV_CIO_CRE_FFLWM__INDEX] = arb_lwm & 0xff;
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_FF_INDEX);
	crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_FFLWM__INDEX);

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_KELVIN) {
		regp->CRTC[NV_CIO_CRE_47] = arb_lwm >> 8;
		crtc_wr_cio_state(crtc, regp, NV_CIO_CRE_47);
	}

	return 0;
}