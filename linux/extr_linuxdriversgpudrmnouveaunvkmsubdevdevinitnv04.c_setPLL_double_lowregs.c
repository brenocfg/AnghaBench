#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct nvkm_pll_vals {int NM2; int NM1; int log2P; scalar_t__ N2; scalar_t__ M2; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_devinit {TYPE_1__ subdev; } ;
struct nvkm_device {int /*<<< orphan*/  bios; } ;
struct nvbios_pll {int bias_p; int max_p; } ;

/* Variables and functions */
 scalar_t__ nvbios_pll_parse (int /*<<< orphan*/ ,int,struct nvbios_pll*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
setPLL_double_lowregs(struct nvkm_devinit *init, u32 NMNMreg,
		      struct nvkm_pll_vals *pv)
{
	/* When setting PLLs, there is a merry game of disabling and enabling
	 * various bits of hardware during the process. This function is a
	 * synthesis of six nv4x traces, nearly each card doing a subtly
	 * different thing. With luck all the necessary bits for each card are
	 * combined herein. Without luck it deviates from each card's formula
	 * so as to not work on any :)
	 */
	struct nvkm_device *device = init->subdev.device;
	uint32_t Preg = NMNMreg - 4;
	bool mpll = Preg == 0x4020;
	uint32_t oldPval = nvkm_rd32(device, Preg);
	uint32_t NMNM = pv->NM2 << 16 | pv->NM1;
	uint32_t Pval = (oldPval & (mpll ? ~(0x77 << 16) : ~(7 << 16))) |
			0xc << 28 | pv->log2P << 16;
	uint32_t saved4600 = 0;
	/* some cards have different maskc040s */
	uint32_t maskc040 = ~(3 << 14), savedc040;
	bool single_stage = !pv->NM2 || pv->N2 == pv->M2;

	if (nvkm_rd32(device, NMNMreg) == NMNM && (oldPval & 0xc0070000) == Pval)
		return;

	if (Preg == 0x4000)
		maskc040 = ~0x333;
	if (Preg == 0x4058)
		maskc040 = ~(0xc << 24);

	if (mpll) {
		struct nvbios_pll info;
		uint8_t Pval2;

		if (nvbios_pll_parse(device->bios, Preg, &info))
			return;

		Pval2 = pv->log2P + info.bias_p;
		if (Pval2 > info.max_p)
			Pval2 = info.max_p;
		Pval |= 1 << 28 | Pval2 << 20;

		saved4600 = nvkm_rd32(device, 0x4600);
		nvkm_wr32(device, 0x4600, saved4600 | 8 << 28);
	}
	if (single_stage)
		Pval |= mpll ? 1 << 12 : 1 << 8;

	nvkm_wr32(device, Preg, oldPval | 1 << 28);
	nvkm_wr32(device, Preg, Pval & ~(4 << 28));
	if (mpll) {
		Pval |= 8 << 20;
		nvkm_wr32(device, 0x4020, Pval & ~(0xc << 28));
		nvkm_wr32(device, 0x4038, Pval & ~(0xc << 28));
	}

	savedc040 = nvkm_rd32(device, 0xc040);
	nvkm_wr32(device, 0xc040, savedc040 & maskc040);

	nvkm_wr32(device, NMNMreg, NMNM);
	if (NMNMreg == 0x4024)
		nvkm_wr32(device, 0x403c, NMNM);

	nvkm_wr32(device, Preg, Pval);
	if (mpll) {
		Pval &= ~(8 << 20);
		nvkm_wr32(device, 0x4020, Pval);
		nvkm_wr32(device, 0x4038, Pval);
		nvkm_wr32(device, 0x4600, saved4600);
	}

	nvkm_wr32(device, 0xc040, savedc040);

	if (mpll) {
		nvkm_wr32(device, 0x4020, Pval & ~(1 << 28));
		nvkm_wr32(device, 0x4038, Pval & ~(1 << 28));
	}
}