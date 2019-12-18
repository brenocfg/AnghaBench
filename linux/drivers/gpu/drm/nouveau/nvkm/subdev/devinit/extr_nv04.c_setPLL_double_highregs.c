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
typedef  int uint32_t ;
typedef  int u32 ;
struct nvkm_pll_vals {int log2P; int NM1; int NM2; int N2; int M2; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct nvkm_devinit {TYPE_1__ subdev; } ;
struct nvkm_device {TYPE_3__* bios; } ;
struct TYPE_5__ {int chip; } ;
struct TYPE_6__ {TYPE_2__ version; } ;

/* Variables and functions */
 int new_ramdac580 (int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int powerctrl_1_shift (int,int) ; 

void
setPLL_double_highregs(struct nvkm_devinit *init, u32 reg1,
		       struct nvkm_pll_vals *pv)
{
	struct nvkm_device *device = init->subdev.device;
	int chip_version = device->bios->version.chip;
	bool nv3035 = chip_version == 0x30 || chip_version == 0x35;
	uint32_t reg2 = reg1 + ((reg1 == 0x680520) ? 0x5c : 0x70);
	uint32_t oldpll1 = nvkm_rd32(device, reg1);
	uint32_t oldpll2 = !nv3035 ? nvkm_rd32(device, reg2) : 0;
	uint32_t pll1 = (oldpll1 & 0xfff80000) | pv->log2P << 16 | pv->NM1;
	uint32_t pll2 = (oldpll2 & 0x7fff0000) | 1 << 31 | pv->NM2;
	uint32_t oldramdac580 = 0, ramdac580 = 0;
	bool single_stage = !pv->NM2 || pv->N2 == pv->M2;	/* nv41+ only */
	uint32_t saved_powerctrl_1 = 0, savedc040 = 0;
	int shift_powerctrl_1 = powerctrl_1_shift(chip_version, reg1);

	/* model specific additions to generic pll1 and pll2 set up above */
	if (nv3035) {
		pll1 = (pll1 & 0xfcc7ffff) | (pv->N2 & 0x18) << 21 |
		       (pv->N2 & 0x7) << 19 | 8 << 4 | (pv->M2 & 7) << 4;
		pll2 = 0;
	}
	if (chip_version > 0x40 && reg1 >= 0x680508) { /* !nv40 */
		oldramdac580 = nvkm_rd32(device, 0x680580);
		ramdac580 = new_ramdac580(reg1, single_stage, oldramdac580);
		if (oldramdac580 != ramdac580)
			oldpll1 = ~0;	/* force mismatch */
		if (single_stage)
			/* magic value used by nvidia in single stage mode */
			pll2 |= 0x011f;
	}
	if (chip_version > 0x70)
		/* magic bits set by the blob (but not the bios) on g71-73 */
		pll1 = (pll1 & 0x7fffffff) | (single_stage ? 0x4 : 0xc) << 28;

	if (oldpll1 == pll1 && oldpll2 == pll2)
		return;	/* already set */

	if (shift_powerctrl_1 >= 0) {
		saved_powerctrl_1 = nvkm_rd32(device, 0x001584);
		nvkm_wr32(device, 0x001584,
			(saved_powerctrl_1 & ~(0xf << shift_powerctrl_1)) |
			1 << shift_powerctrl_1);
	}

	if (chip_version >= 0x40) {
		int shift_c040 = 14;

		switch (reg1) {
		case 0x680504:
			shift_c040 += 2; /* fall through */
		case 0x680500:
			shift_c040 += 2; /* fall through */
		case 0x680520:
			shift_c040 += 2; /* fall through */
		case 0x680508:
			shift_c040 += 2;
		}

		savedc040 = nvkm_rd32(device, 0xc040);
		if (shift_c040 != 14)
			nvkm_wr32(device, 0xc040, savedc040 & ~(3 << shift_c040));
	}

	if (oldramdac580 != ramdac580)
		nvkm_wr32(device, 0x680580, ramdac580);

	if (!nv3035)
		nvkm_wr32(device, reg2, pll2);
	nvkm_wr32(device, reg1, pll1);

	if (shift_powerctrl_1 >= 0)
		nvkm_wr32(device, 0x001584, saved_powerctrl_1);
	if (chip_version >= 0x40)
		nvkm_wr32(device, 0xc040, savedc040);
}