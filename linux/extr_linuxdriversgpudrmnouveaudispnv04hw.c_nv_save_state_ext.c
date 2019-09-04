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
struct nv04_mode_state {struct nv04_crtc_reg* crtc_reg; } ;
struct nv04_crtc_reg {void* fb_start; int /*<<< orphan*/ * CR58; void* crtc_cfg; void* cursor_cfg; void* crtc_eng_ctrl; void* crtc_850; void* gpio_ext; void* crtc_834; void* crtc_830; } ;
struct TYPE_4__ {scalar_t__ family; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
struct TYPE_6__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 void* NVReadCRTC (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVReadVgaCrtc5758 (struct drm_device*,int,int) ; 
 int NV_CIO_CRE_21 ; 
 int NV_CIO_CRE_42 ; 
 int NV_CIO_CRE_47 ; 
 int NV_CIO_CRE_49 ; 
 int NV_CIO_CRE_4B ; 
 int NV_CIO_CRE_53 ; 
 int NV_CIO_CRE_54 ; 
 int NV_CIO_CRE_59 ; 
 int NV_CIO_CRE_5B ; 
 int NV_CIO_CRE_85 ; 
 int NV_CIO_CRE_86 ; 
 int NV_CIO_CRE_CSB ; 
 int NV_CIO_CRE_EBR_INDEX ; 
 int NV_CIO_CRE_ENH_INDEX ; 
 int NV_CIO_CRE_FFLWM__INDEX ; 
 int NV_CIO_CRE_FF_INDEX ; 
 int NV_CIO_CRE_HCUR_ADDR0_INDEX ; 
 int NV_CIO_CRE_HCUR_ADDR1_INDEX ; 
 int NV_CIO_CRE_HCUR_ADDR2_INDEX ; 
 int NV_CIO_CRE_HEB__INDEX ; 
 int NV_CIO_CRE_ILACE__INDEX ; 
 int NV_CIO_CRE_LCD__INDEX ; 
 int NV_CIO_CRE_LSR_INDEX ; 
 int NV_CIO_CRE_PIXEL_INDEX ; 
 int NV_CIO_CRE_RPC0_INDEX ; 
 int NV_CIO_CRE_RPC1_INDEX ; 
 int NV_CIO_CRE_SCRATCH3__INDEX ; 
 int NV_CIO_CRE_SCRATCH4__INDEX ; 
 int NV_CIO_CRE_TVOUT_LATENCY ; 
 scalar_t__ NV_DEVICE_INFO_V0_CELSIUS ; 
 scalar_t__ NV_DEVICE_INFO_V0_CURIE ; 
 scalar_t__ NV_DEVICE_INFO_V0_KELVIN ; 
 scalar_t__ NV_DEVICE_INFO_V0_RANKINE ; 
 int /*<<< orphan*/  NV_PCRTC_830 ; 
 int /*<<< orphan*/  NV_PCRTC_834 ; 
 int /*<<< orphan*/  NV_PCRTC_850 ; 
 int /*<<< orphan*/  NV_PCRTC_CONFIG ; 
 int /*<<< orphan*/  NV_PCRTC_CURSOR_CONFIG ; 
 int /*<<< orphan*/  NV_PCRTC_ENGINE_CTRL ; 
 int /*<<< orphan*/  NV_PCRTC_GPIO_EXT ; 
 int /*<<< orphan*/  NV_PCRTC_START ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 scalar_t__ nv_gf4_disp_arch (struct drm_device*) ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 
 int /*<<< orphan*/  rd_cio_state (struct drm_device*,int,struct nv04_crtc_reg*,int) ; 

__attribute__((used)) static void
nv_save_state_ext(struct drm_device *dev, int head,
		  struct nv04_mode_state *state)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nv04_crtc_reg *regp = &state->crtc_reg[head];
	int i;

	rd_cio_state(dev, head, regp, NV_CIO_CRE_LCD__INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_RPC0_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_RPC1_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_LSR_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_PIXEL_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_HEB__INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_ENH_INDEX);

	rd_cio_state(dev, head, regp, NV_CIO_CRE_FF_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_FFLWM__INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_21);

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_KELVIN)
		rd_cio_state(dev, head, regp, NV_CIO_CRE_47);

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE)
		rd_cio_state(dev, head, regp, 0x9f);

	rd_cio_state(dev, head, regp, NV_CIO_CRE_49);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR0_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR1_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_HCUR_ADDR2_INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_ILACE__INDEX);

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS) {
		regp->crtc_830 = NVReadCRTC(dev, head, NV_PCRTC_830);
		regp->crtc_834 = NVReadCRTC(dev, head, NV_PCRTC_834);

		if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_RANKINE)
			regp->gpio_ext = NVReadCRTC(dev, head, NV_PCRTC_GPIO_EXT);

		if (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
			regp->crtc_850 = NVReadCRTC(dev, head, NV_PCRTC_850);

		if (nv_two_heads(dev))
			regp->crtc_eng_ctrl = NVReadCRTC(dev, head, NV_PCRTC_ENGINE_CTRL);
		regp->cursor_cfg = NVReadCRTC(dev, head, NV_PCRTC_CURSOR_CONFIG);
	}

	regp->crtc_cfg = NVReadCRTC(dev, head, NV_PCRTC_CONFIG);

	rd_cio_state(dev, head, regp, NV_CIO_CRE_SCRATCH3__INDEX);
	rd_cio_state(dev, head, regp, NV_CIO_CRE_SCRATCH4__INDEX);
	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS) {
		rd_cio_state(dev, head, regp, NV_CIO_CRE_EBR_INDEX);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_CSB);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_4B);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_TVOUT_LATENCY);
	}
	/* NV11 and NV20 don't have this, they stop at 0x52. */
	if (nv_gf4_disp_arch(dev)) {
		rd_cio_state(dev, head, regp, NV_CIO_CRE_42);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_53);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_54);

		for (i = 0; i < 0x10; i++)
			regp->CR58[i] = NVReadVgaCrtc5758(dev, head, i);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_59);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_5B);

		rd_cio_state(dev, head, regp, NV_CIO_CRE_85);
		rd_cio_state(dev, head, regp, NV_CIO_CRE_86);
	}

	regp->fb_start = NVReadCRTC(dev, head, NV_PCRTC_START);
}