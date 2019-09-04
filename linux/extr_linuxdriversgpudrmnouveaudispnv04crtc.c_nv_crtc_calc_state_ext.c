#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct nvkm_pll_vals {int /*<<< orphan*/  log2P; int /*<<< orphan*/  M1; int /*<<< orphan*/  N1; int /*<<< orphan*/  M2; int /*<<< orphan*/  N2; scalar_t__ NM2; } ;
struct nvkm_clk {int /*<<< orphan*/  (* pll_calc ) (struct nvkm_clk*,struct nvbios_pll*,int,struct nvkm_pll_vals*) ;} ;
struct nvkm_bios {int dummy; } ;
struct TYPE_8__ {int max_freq; } ;
struct nvbios_pll {int /*<<< orphan*/  vco2; TYPE_1__ vco1; } ;
struct nv04_mode_state {int pllsel; struct nv04_crtc_reg* crtc_reg; } ;
struct nv04_crtc_reg {struct nvkm_pll_vals pllvals; } ;
struct TYPE_9__ {int chipset; scalar_t__ family; } ;
struct TYPE_12__ {TYPE_2__ info; } ;
struct TYPE_10__ {TYPE_5__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct TYPE_11__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  (* set_offset ) (struct nouveau_crtc*,int /*<<< orphan*/ ) ;} ;
struct nouveau_crtc {size_t index; TYPE_4__ cursor; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_13__ {struct nv04_mode_state mode_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ NV_DEVICE_INFO_V0_CURIE ; 
 int NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_MPLL ; 
 int NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_NVPLL ; 
 int NV_PRAMDAC_PLL_COEFF_SELECT_USE_VPLL2_TRUE ; 
 int PLLSEL_TV_MASK ; 
 int PLLSEL_VPLL1_MASK ; 
 int PLLSEL_VPLL2_MASK ; 
 int /*<<< orphan*/  PLL_VPLL0 ; 
 int /*<<< orphan*/  PLL_VPLL1 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 TYPE_7__* nv04_display (struct drm_device*) ; 
 scalar_t__ nvbios_pll_parse (struct nvkm_bios*,int /*<<< orphan*/ ,struct nvbios_pll*) ; 
 struct nvkm_bios* nvxx_bios (TYPE_5__*) ; 
 struct nvkm_clk* nvxx_clk (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_clk*,struct nvbios_pll*,int,struct nvkm_pll_vals*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nv_crtc_calc_state_ext(struct drm_crtc *crtc, struct drm_display_mode * mode, int dot_clock)
{
	struct drm_device *dev = crtc->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvkm_bios *bios = nvxx_bios(&drm->client.device);
	struct nvkm_clk *clk = nvxx_clk(&drm->client.device);
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nv04_mode_state *state = &nv04_display(dev)->mode_reg;
	struct nv04_crtc_reg *regp = &state->crtc_reg[nv_crtc->index];
	struct nvkm_pll_vals *pv = &regp->pllvals;
	struct nvbios_pll pll_lim;

	if (nvbios_pll_parse(bios, nv_crtc->index ? PLL_VPLL1 : PLL_VPLL0,
			    &pll_lim))
		return;

	/* NM2 == 0 is used to determine single stage mode on two stage plls */
	pv->NM2 = 0;

	/* for newer nv4x the blob uses only the first stage of the vpll below a
	 * certain clock.  for a certain nv4b this is 150MHz.  since the max
	 * output frequency of the first stage for this card is 300MHz, it is
	 * assumed the threshold is given by vco1 maxfreq/2
	 */
	/* for early nv4x, specifically nv40 and *some* nv43 (devids 0 and 6,
	 * not 8, others unknown), the blob always uses both plls.  no problem
	 * has yet been observed in allowing the use a single stage pll on all
	 * nv43 however.  the behaviour of single stage use is untested on nv40
	 */
	if (drm->client.device.info.chipset > 0x40 && dot_clock <= (pll_lim.vco1.max_freq / 2))
		memset(&pll_lim.vco2, 0, sizeof(pll_lim.vco2));


	if (!clk->pll_calc(clk, &pll_lim, dot_clock, pv))
		return;

	state->pllsel &= PLLSEL_VPLL1_MASK | PLLSEL_VPLL2_MASK | PLLSEL_TV_MASK;

	/* The blob uses this always, so let's do the same */
	if (drm->client.device.info.family == NV_DEVICE_INFO_V0_CURIE)
		state->pllsel |= NV_PRAMDAC_PLL_COEFF_SELECT_USE_VPLL2_TRUE;
	/* again nv40 and some nv43 act more like nv3x as described above */
	if (drm->client.device.info.chipset < 0x41)
		state->pllsel |= NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_MPLL |
				 NV_PRAMDAC_PLL_COEFF_SELECT_SOURCE_PROG_NVPLL;
	state->pllsel |= nv_crtc->index ? PLLSEL_VPLL2_MASK : PLLSEL_VPLL1_MASK;

	if (pv->NM2)
		NV_DEBUG(drm, "vpll: n1 %d n2 %d m1 %d m2 %d log2p %d\n",
			 pv->N1, pv->N2, pv->M1, pv->M2, pv->log2P);
	else
		NV_DEBUG(drm, "vpll: n %d m %d log2p %d\n",
			 pv->N1, pv->M1, pv->log2P);

	nv_crtc->cursor.set_offset(nv_crtc, nv_crtc->cursor.offset);
}