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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct nvkm_cstate {int /*<<< orphan*/ * domain; int /*<<< orphan*/  voltage; } ;
struct nvkm_pstate {int /*<<< orphan*/  head; int /*<<< orphan*/  pstate; int /*<<< orphan*/  pcie_width; int /*<<< orphan*/  pcie_speed; int /*<<< orphan*/  fanspeed; int /*<<< orphan*/  list; struct nvkm_cstate base; } ;
struct nvkm_domain {scalar_t__ name; int flags; int /*<<< orphan*/  bios; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct nvkm_clk {int /*<<< orphan*/  state_nr; int /*<<< orphan*/  states; struct nvkm_domain* domains; TYPE_2__ subdev; } ;
struct nvkm_bios {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  freq; } ;
struct nvbios_perfS {TYPE_3__ v40; } ;
struct nvbios_perfE {int pstate; int /*<<< orphan*/  disp; int /*<<< orphan*/  vdec; int /*<<< orphan*/  memory; int /*<<< orphan*/  shader; int /*<<< orphan*/  core; int /*<<< orphan*/  voltage; int /*<<< orphan*/  pcie_width; int /*<<< orphan*/  pcie_speed; int /*<<< orphan*/  fanspeed; } ;
struct nvbios_cstepE {int index; } ;
struct TYPE_4__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NVKM_CLK_DOM_FLAG_CORE ; 
 struct nvkm_pstate* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t nv_clk_src_core ; 
 size_t nv_clk_src_dom6 ; 
 scalar_t__ nv_clk_src_max ; 
 size_t nv_clk_src_mem ; 
 size_t nv_clk_src_shader ; 
 size_t nv_clk_src_vdec ; 
 scalar_t__ nvbios_cstepEm (struct nvkm_bios*,int /*<<< orphan*/ ,int*,int*,struct nvbios_cstepE*) ; 
 scalar_t__ nvbios_perfEp (struct nvkm_bios*,int,int*,int*,int*,int*,struct nvbios_perfE*) ; 
 scalar_t__ nvbios_perfSp (struct nvkm_bios*,scalar_t__,int /*<<< orphan*/ ,int*,int*,int,int,struct nvbios_perfS*) ; 
 int /*<<< orphan*/  nvkm_clk_adjust (struct nvkm_clk*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_cstate_new (struct nvkm_clk*,int,struct nvkm_pstate*) ; 
 int /*<<< orphan*/  nvkm_pstate_info (struct nvkm_clk*,struct nvkm_pstate*) ; 

__attribute__((used)) static int
nvkm_pstate_new(struct nvkm_clk *clk, int idx)
{
	struct nvkm_bios *bios = clk->subdev.device->bios;
	const struct nvkm_domain *domain = clk->domains - 1;
	struct nvkm_pstate *pstate;
	struct nvkm_cstate *cstate;
	struct nvbios_cstepE cstepE;
	struct nvbios_perfE perfE;
	u8  ver, hdr, cnt, len;
	u32 data;

	data = nvbios_perfEp(bios, idx, &ver, &hdr, &cnt, &len, &perfE);
	if (!data)
		return -EINVAL;
	if (perfE.pstate == 0xff)
		return 0;

	pstate = kzalloc(sizeof(*pstate), GFP_KERNEL);
	cstate = &pstate->base;
	if (!pstate)
		return -ENOMEM;

	INIT_LIST_HEAD(&pstate->list);

	pstate->pstate = perfE.pstate;
	pstate->fanspeed = perfE.fanspeed;
	pstate->pcie_speed = perfE.pcie_speed;
	pstate->pcie_width = perfE.pcie_width;
	cstate->voltage = perfE.voltage;
	cstate->domain[nv_clk_src_core] = perfE.core;
	cstate->domain[nv_clk_src_shader] = perfE.shader;
	cstate->domain[nv_clk_src_mem] = perfE.memory;
	cstate->domain[nv_clk_src_vdec] = perfE.vdec;
	cstate->domain[nv_clk_src_dom6] = perfE.disp;

	while (ver >= 0x40 && (++domain)->name != nv_clk_src_max) {
		struct nvbios_perfS perfS;
		u8  sver = ver, shdr = hdr;
		u32 perfSe = nvbios_perfSp(bios, data, domain->bios,
					  &sver, &shdr, cnt, len, &perfS);
		if (perfSe == 0 || sver != 0x40)
			continue;

		if (domain->flags & NVKM_CLK_DOM_FLAG_CORE) {
			perfS.v40.freq = nvkm_clk_adjust(clk, false,
							 pstate->pstate,
							 domain->bios,
							 perfS.v40.freq);
		}

		cstate->domain[domain->name] = perfS.v40.freq;
	}

	data = nvbios_cstepEm(bios, pstate->pstate, &ver, &hdr, &cstepE);
	if (data) {
		int idx = cstepE.index;
		do {
			nvkm_cstate_new(clk, idx, pstate);
		} while(idx--);
	}

	nvkm_pstate_info(clk, pstate);
	list_add_tail(&pstate->head, &clk->states);
	clk->state_nr++;
	return 0;
}