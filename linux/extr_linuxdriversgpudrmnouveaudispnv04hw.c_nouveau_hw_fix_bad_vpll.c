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
struct nvkm_pll_vals {scalar_t__ M1; scalar_t__ N1; scalar_t__ log2P; } ;
struct nvkm_clk {int /*<<< orphan*/  (* pll_prog ) (struct nvkm_clk*,int /*<<< orphan*/ ,struct nvkm_pll_vals*) ;} ;
struct nvkm_bios {int dummy; } ;
struct nvif_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ min_m; scalar_t__ max_m; scalar_t__ min_n; scalar_t__ max_n; } ;
struct nvbios_pll {scalar_t__ max_p; scalar_t__ max_p_usable; int /*<<< orphan*/  reg; TYPE_2__ vco1; } ;
struct TYPE_3__ {struct nvif_device device; } ;
struct nouveau_drm {TYPE_1__ client; } ;
struct drm_device {int dummy; } ;
typedef  enum nvbios_pll_type { ____Placeholder_nvbios_pll_type } nvbios_pll_type ;

/* Variables and functions */
 int /*<<< orphan*/  NV_WARN (struct nouveau_drm*,char*,int) ; 
 int PLL_VPLL0 ; 
 int PLL_VPLL1 ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_hw_get_pllvals (struct drm_device*,int,struct nvkm_pll_vals*) ; 
 scalar_t__ nvbios_pll_parse (struct nvkm_bios*,int,struct nvbios_pll*) ; 
 struct nvkm_bios* nvxx_bios (struct nvif_device*) ; 
 struct nvkm_clk* nvxx_clk (struct nvif_device*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_clk*,int /*<<< orphan*/ ,struct nvkm_pll_vals*) ; 

__attribute__((used)) static void
nouveau_hw_fix_bad_vpll(struct drm_device *dev, int head)
{
	/* the vpll on an unused head can come up with a random value, way
	 * beyond the pll limits.  for some reason this causes the chip to
	 * lock up when reading the dac palette regs, so set a valid pll here
	 * when such a condition detected.  only seen on nv11 to date
	 */

	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvif_device *device = &drm->client.device;
	struct nvkm_clk *clk = nvxx_clk(device);
	struct nvkm_bios *bios = nvxx_bios(device);
	struct nvbios_pll pll_lim;
	struct nvkm_pll_vals pv;
	enum nvbios_pll_type pll = head ? PLL_VPLL1 : PLL_VPLL0;

	if (nvbios_pll_parse(bios, pll, &pll_lim))
		return;
	nouveau_hw_get_pllvals(dev, pll, &pv);

	if (pv.M1 >= pll_lim.vco1.min_m && pv.M1 <= pll_lim.vco1.max_m &&
	    pv.N1 >= pll_lim.vco1.min_n && pv.N1 <= pll_lim.vco1.max_n &&
	    pv.log2P <= pll_lim.max_p)
		return;

	NV_WARN(drm, "VPLL %d outwith limits, attempting to fix\n", head + 1);

	/* set lowest clock within static limits */
	pv.M1 = pll_lim.vco1.max_m;
	pv.N1 = pll_lim.vco1.min_n;
	pv.log2P = pll_lim.max_p_usable;
	clk->pll_prog(clk, pll_lim.reg, &pv);
}