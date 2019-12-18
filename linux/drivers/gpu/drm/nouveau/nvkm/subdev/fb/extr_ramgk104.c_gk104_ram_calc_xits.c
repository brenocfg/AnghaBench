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
struct nvkm_subdev {TYPE_2__* device; } ;
struct nvkm_ram_data {int freq; } ;
struct TYPE_10__ {int refclk; } ;
struct TYPE_8__ {int max_freq; } ;
struct TYPE_13__ {TYPE_1__ vco1; } ;
struct gk104_ramfuc {int /*<<< orphan*/  r_mr; TYPE_3__ mempll; TYPE_7__ refpll; } ;
struct TYPE_12__ {int* mr; int freq; int type; TYPE_4__* fb; } ;
struct gk104_ram {int mode; int from; int /*<<< orphan*/  pnuts; TYPE_5__ base; int /*<<< orphan*/  P1; int /*<<< orphan*/  M1; int /*<<< orphan*/  fN1; int /*<<< orphan*/  N1; int /*<<< orphan*/  P2; int /*<<< orphan*/  M2; int /*<<< orphan*/  N2; struct gk104_ramfuc fuc; } ;
struct TYPE_11__ {struct nvkm_subdev subdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  crystal; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOSYS ; 
#define  NVKM_RAM_TYPE_DDR3 129 
#define  NVKM_RAM_TYPE_GDDR5 128 
 int gk104_pll_calc_hiclk (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int gk104_ram_calc_gddr5 (struct gk104_ram*,int) ; 
 int gk104_ram_calc_sddr3 (struct gk104_ram*,int) ; 
 int gt215_pll_calc (struct nvkm_subdev*,TYPE_7__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* mr ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,int) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int nvkm_gddr5_calc (TYPE_5__*,int) ; 
 int nvkm_sddr3_calc (TYPE_5__*) ; 
 scalar_t__ ram_have (struct gk104_ramfuc*,int) ; 
 int ram_init (struct gk104_ramfuc*,TYPE_4__*) ; 
 int ram_rd32 (struct gk104_ramfuc*,int) ; 

__attribute__((used)) static int
gk104_ram_calc_xits(struct gk104_ram *ram, struct nvkm_ram_data *next)
{
	struct gk104_ramfuc *fuc = &ram->fuc;
	struct nvkm_subdev *subdev = &ram->base.fb->subdev;
	int refclk, i;
	int ret;

	ret = ram_init(fuc, ram->base.fb);
	if (ret)
		return ret;

	ram->mode = (next->freq > fuc->refpll.vco1.max_freq) ? 2 : 1;
	ram->from = ram_rd32(fuc, 0x1373f4) & 0x0000000f;

	/* XXX: this is *not* what nvidia do.  on fermi nvidia generally
	 * select, based on some unknown condition, one of the two possible
	 * reference frequencies listed in the vbios table for mempll and
	 * program refpll to that frequency.
	 *
	 * so far, i've seen very weird values being chosen by nvidia on
	 * kepler boards, no idea how/why they're chosen.
	 */
	refclk = next->freq;
	if (ram->mode == 2) {
		ret = gk104_pll_calc_hiclk(next->freq, subdev->device->crystal,
				&ram->N1, &ram->fN1, &ram->M1, &ram->P1,
				&ram->N2, &ram->M2, &ram->P2);
		fuc->mempll.refclk = ret;
		if (ret <= 0) {
			nvkm_error(subdev, "unable to calc plls\n");
			return -EINVAL;
		}
		nvkm_debug(subdev, "successfully calced PLLs for clock %i kHz"
				" (refclock: %i kHz)\n", next->freq, ret);
	} else {
		/* calculate refpll coefficients */
		ret = gt215_pll_calc(subdev, &fuc->refpll, refclk, &ram->N1,
				     &ram->fN1, &ram->M1, &ram->P1);
		fuc->mempll.refclk = ret;
		if (ret <= 0) {
			nvkm_error(subdev, "unable to calc refpll\n");
			return -EINVAL;
		}
	}

	for (i = 0; i < ARRAY_SIZE(fuc->r_mr); i++) {
		if (ram_have(fuc, mr[i]))
			ram->base.mr[i] = ram_rd32(fuc, mr[i]);
	}
	ram->base.freq = next->freq;

	switch (ram->base.type) {
	case NVKM_RAM_TYPE_DDR3:
		ret = nvkm_sddr3_calc(&ram->base);
		if (ret == 0)
			ret = gk104_ram_calc_sddr3(ram, next->freq);
		break;
	case NVKM_RAM_TYPE_GDDR5:
		ret = nvkm_gddr5_calc(&ram->base, ram->pnuts != 0);
		if (ret == 0)
			ret = gk104_ram_calc_gddr5(ram, next->freq);
		break;
	default:
		ret = -ENOSYS;
		break;
	}

	return ret;
}