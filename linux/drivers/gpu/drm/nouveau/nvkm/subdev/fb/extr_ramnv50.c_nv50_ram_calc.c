#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_subdev {TYPE_3__* device; } ;
struct TYPE_12__ {int ramcfg_timing; int rammap_00_16_40; int ramcfg_00_07; int ramcfg_00_06; int ramcfg_00_05; int ramcfg_00_09; int ramcfg_00_08; scalar_t__ ramcfg_00_03_02; scalar_t__ rammap_00_17_02; int /*<<< orphan*/  ramcfg_DLLoff; scalar_t__ timing_10_ODT; scalar_t__ rammap_00_16_20; scalar_t__ ramcfg_00_04_20; scalar_t__ ramcfg_00_04_04; int /*<<< orphan*/  ramcfg_00_03_08; scalar_t__ ramcfg_00_03_01; int /*<<< orphan*/  ramcfg_FBVDDQ; int /*<<< orphan*/  ramcfg_00_04_02; } ;
struct nvkm_ram_data {int freq; TYPE_5__ bios; } ;
struct nvkm_ram {int dummy; } ;
struct nvkm_bios {int dummy; } ;
struct TYPE_9__ {scalar_t__ max_freq; } ;
struct nvbios_pll {int bias_p; TYPE_2__ vco2; } ;
struct nvbios_perfE {int memory; } ;
struct nv50_ramseq {int dummy; } ;
struct TYPE_11__ {int* mr; int type; struct nvkm_ram_data* next; struct nvkm_ram_data target; TYPE_1__* fb; } ;
struct nv50_ram {TYPE_4__ base; struct nv50_ramseq hwsq; } ;
struct TYPE_10__ {int chipset; struct nvkm_bios* bios; } ;
struct TYPE_8__ {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
#define  NVKM_RAM_TYPE_DDR2 129 
#define  NVKM_RAM_TYPE_GDDR3 128 
 int* mr ; 
 int nv04_pll_calc (struct nvkm_subdev*,struct nvbios_pll*,int,int*,int*,int*,int*,int*) ; 
 struct nv50_ram* nv50_ram (struct nvkm_ram*) ; 
 int /*<<< orphan*/  nv50_ram_gpio (struct nv50_ramseq*,int,int) ; 
 int /*<<< orphan*/  nv50_ram_timing_calc (struct nv50_ram*,int*) ; 
 int /*<<< orphan*/  nv50_ram_timing_read (struct nv50_ram*,int*) ; 
 int nvbios_perfEp (struct nvkm_bios*,int /*<<< orphan*/ ,int*,int*,int*,int*,struct nvbios_perfE*) ; 
 int nvbios_pll_parse (struct nvkm_bios*,int,struct nvbios_pll*) ; 
 int nvbios_ramcfg_index (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvbios_rammapEp_from_perf (struct nvkm_bios*,int,int,TYPE_5__*) ; 
 int nvbios_rammapSp_from_perf (struct nvkm_bios*,int,int,int,TYPE_5__*) ; 
 int nvbios_timingEp (struct nvkm_bios*,int,int*,int*,int*,int*,TYPE_5__*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,...) ; 
 int nvkm_gddr3_calc (TYPE_4__*) ; 
 int /*<<< orphan*/  nvkm_sddr2_dll_reset (struct nv50_ramseq*) ; 
 int ram_init (struct nv50_ramseq*,struct nvkm_subdev*) ; 
 int /*<<< orphan*/  ram_mask (struct nv50_ramseq*,int,int,int) ; 
 int /*<<< orphan*/  ram_nsec (struct nv50_ramseq*,int) ; 
 int /*<<< orphan*/  ram_nuke (struct nv50_ramseq*,int) ; 
 int ram_rd32 (struct nv50_ramseq*,int) ; 
 int /*<<< orphan*/  ram_setf (struct nv50_ramseq*,int,int) ; 
 int /*<<< orphan*/  ram_wait (struct nv50_ramseq*,int,int) ; 
 int /*<<< orphan*/  ram_wait_vblank (struct nv50_ramseq*) ; 
 int /*<<< orphan*/  ram_wr32 (struct nv50_ramseq*,int,int) ; 

__attribute__((used)) static int
nv50_ram_calc(struct nvkm_ram *base, u32 freq)
{
	struct nv50_ram *ram = nv50_ram(base);
	struct nv50_ramseq *hwsq = &ram->hwsq;
	struct nvkm_subdev *subdev = &ram->base.fb->subdev;
	struct nvkm_bios *bios = subdev->device->bios;
	struct nvbios_perfE perfE;
	struct nvbios_pll mpll;
	struct nvkm_ram_data *next;
	u8  ver, hdr, cnt, len, strap, size;
	u32 data;
	u32 r100da0, r004008, unk710, unk714, unk718, unk71c;
	int N1, M1, N2, M2, P;
	int ret, i;
	u32 timing[9];

	next = &ram->base.target;
	next->freq = freq;
	ram->base.next = next;

	/* lookup closest matching performance table entry for frequency */
	i = 0;
	do {
		data = nvbios_perfEp(bios, i++, &ver, &hdr, &cnt,
				     &size, &perfE);
		if (!data || (ver < 0x25 || ver >= 0x40) ||
		    (size < 2)) {
			nvkm_error(subdev, "invalid/missing perftab entry\n");
			return -EINVAL;
		}
	} while (perfE.memory < freq);

	nvbios_rammapEp_from_perf(bios, data, hdr, &next->bios);

	/* locate specific data set for the attached memory */
	strap = nvbios_ramcfg_index(subdev);
	if (strap >= cnt) {
		nvkm_error(subdev, "invalid ramcfg strap\n");
		return -EINVAL;
	}

	data = nvbios_rammapSp_from_perf(bios, data + hdr, size, strap,
			&next->bios);
	if (!data) {
		nvkm_error(subdev, "invalid/missing rammap entry ");
		return -EINVAL;
	}

	/* lookup memory timings, if bios says they're present */
	if (next->bios.ramcfg_timing != 0xff) {
		data = nvbios_timingEp(bios, next->bios.ramcfg_timing,
					&ver, &hdr, &cnt, &len, &next->bios);
		if (!data || ver != 0x10 || hdr < 0x12) {
			nvkm_error(subdev, "invalid/missing timing entry "
				 "%02x %04x %02x %02x\n",
				 strap, data, ver, hdr);
			return -EINVAL;
		}
		nv50_ram_timing_calc(ram, timing);
	} else {
		nv50_ram_timing_read(ram, timing);
	}

	ret = ram_init(hwsq, subdev);
	if (ret)
		return ret;

	/* Determine ram-specific MR values */
	ram->base.mr[0] = ram_rd32(hwsq, mr[0]);
	ram->base.mr[1] = ram_rd32(hwsq, mr[1]);
	ram->base.mr[2] = ram_rd32(hwsq, mr[2]);

	switch (ram->base.type) {
	case NVKM_RAM_TYPE_GDDR3:
		ret = nvkm_gddr3_calc(&ram->base);
		break;
	default:
		ret = -ENOSYS;
		break;
	}

	if (ret) {
		nvkm_error(subdev, "Could not calculate MR\n");
		return ret;
	}

	if (subdev->device->chipset <= 0x96 && !next->bios.ramcfg_00_03_02)
		ram_mask(hwsq, 0x100710, 0x00000200, 0x00000000);

	/* Always disable this bit during reclock */
	ram_mask(hwsq, 0x100200, 0x00000800, 0x00000000);

	ram_wait_vblank(hwsq);
	ram_wr32(hwsq, 0x611200, 0x00003300);
	ram_wr32(hwsq, 0x002504, 0x00000001); /* block fifo */
	ram_nsec(hwsq, 8000);
	ram_setf(hwsq, 0x10, 0x00); /* disable fb */
	ram_wait(hwsq, 0x00, 0x01); /* wait for fb disabled */
	ram_nsec(hwsq, 2000);

	if (next->bios.timing_10_ODT)
		nv50_ram_gpio(hwsq, 0x2e, 1);

	ram_wr32(hwsq, 0x1002d4, 0x00000001); /* precharge */
	ram_wr32(hwsq, 0x1002d0, 0x00000001); /* refresh */
	ram_wr32(hwsq, 0x1002d0, 0x00000001); /* refresh */
	ram_wr32(hwsq, 0x100210, 0x00000000); /* disable auto-refresh */
	ram_wr32(hwsq, 0x1002dc, 0x00000001); /* enable self-refresh */

	ret = nvbios_pll_parse(bios, 0x004008, &mpll);
	mpll.vco2.max_freq = 0;
	if (ret >= 0) {
		ret = nv04_pll_calc(subdev, &mpll, freq,
				    &N1, &M1, &N2, &M2, &P);
		if (ret <= 0)
			ret = -EINVAL;
	}

	if (ret < 0)
		return ret;

	/* XXX: 750MHz seems rather arbitrary */
	if (freq <= 750000) {
		r100da0 = 0x00000010;
		r004008 = 0x90000000;
	} else {
		r100da0 = 0x00000000;
		r004008 = 0x80000000;
	}

	r004008 |= (mpll.bias_p << 19) | (P << 22) | (P << 16);

	ram_mask(hwsq, 0x00c040, 0xc000c000, 0x0000c000);
	/* XXX: Is rammap_00_16_40 the DLL bit we've seen in GT215? Why does
	 * it have a different rammap bit from DLLoff? */
	ram_mask(hwsq, 0x004008, 0x00004200, 0x00000200 |
			next->bios.rammap_00_16_40 << 14);
	ram_mask(hwsq, 0x00400c, 0x0000ffff, (N1 << 8) | M1);
	ram_mask(hwsq, 0x004008, 0x91ff0000, r004008);

	/* XXX: GDDR3 only? */
	if (subdev->device->chipset >= 0x92)
		ram_wr32(hwsq, 0x100da0, r100da0);

	nv50_ram_gpio(hwsq, 0x18, !next->bios.ramcfg_FBVDDQ);
	ram_nsec(hwsq, 64000); /*XXX*/
	ram_nsec(hwsq, 32000); /*XXX*/

	ram_mask(hwsq, 0x004008, 0x00002200, 0x00002000);

	ram_wr32(hwsq, 0x1002dc, 0x00000000); /* disable self-refresh */
	ram_wr32(hwsq, 0x1002d4, 0x00000001); /* disable self-refresh */
	ram_wr32(hwsq, 0x100210, 0x80000000); /* enable auto-refresh */

	ram_nsec(hwsq, 12000);

	switch (ram->base.type) {
	case NVKM_RAM_TYPE_DDR2:
		ram_nuke(hwsq, mr[0]); /* force update */
		ram_mask(hwsq, mr[0], 0x000, 0x000);
		break;
	case NVKM_RAM_TYPE_GDDR3:
		ram_nuke(hwsq, mr[1]); /* force update */
		ram_wr32(hwsq, mr[1], ram->base.mr[1]);
		ram_nuke(hwsq, mr[0]); /* force update */
		ram_wr32(hwsq, mr[0], ram->base.mr[0]);
		break;
	default:
		break;
	}

	ram_mask(hwsq, timing[3], 0xffffffff, timing[3]);
	ram_mask(hwsq, timing[1], 0xffffffff, timing[1]);
	ram_mask(hwsq, timing[6], 0xffffffff, timing[6]);
	ram_mask(hwsq, timing[7], 0xffffffff, timing[7]);
	ram_mask(hwsq, timing[8], 0xffffffff, timing[8]);
	ram_mask(hwsq, timing[0], 0xffffffff, timing[0]);
	ram_mask(hwsq, timing[2], 0xffffffff, timing[2]);
	ram_mask(hwsq, timing[4], 0xffffffff, timing[4]);
	ram_mask(hwsq, timing[5], 0xffffffff, timing[5]);

	if (!next->bios.ramcfg_00_03_02)
		ram_mask(hwsq, 0x10021c, 0x00010000, 0x00000000);
	ram_mask(hwsq, 0x100200, 0x00001000, !next->bios.ramcfg_00_04_02 << 12);

	/* XXX: A lot of this could be "chipset"/"ram type" specific stuff */
	unk710  = ram_rd32(hwsq, 0x100710) & ~0x00000100;
	unk714  = ram_rd32(hwsq, 0x100714) & ~0xf0000020;
	unk718  = ram_rd32(hwsq, 0x100718) & ~0x00000100;
	unk71c  = ram_rd32(hwsq, 0x10071c) & ~0x00000100;
	if (subdev->device->chipset <= 0x96) {
		unk710 &= ~0x0000006e;
		unk714 &= ~0x00000100;

		if (!next->bios.ramcfg_00_03_08)
			unk710 |= 0x00000060;
		if (!next->bios.ramcfg_FBVDDQ)
			unk714 |= 0x00000100;
		if ( next->bios.ramcfg_00_04_04)
			unk710 |= 0x0000000e;
	} else {
		unk710 &= ~0x00000001;

		if (!next->bios.ramcfg_00_03_08)
			unk710 |= 0x00000001;
	}

	if ( next->bios.ramcfg_00_03_01)
		unk71c |= 0x00000100;
	if ( next->bios.ramcfg_00_03_02)
		unk710 |= 0x00000100;
	if (!next->bios.ramcfg_00_03_08)
		unk714 |= 0x00000020;
	if ( next->bios.ramcfg_00_04_04)
		unk714 |= 0x70000000;
	if ( next->bios.ramcfg_00_04_20)
		unk718 |= 0x00000100;

	ram_mask(hwsq, 0x100714, 0xffffffff, unk714);
	ram_mask(hwsq, 0x10071c, 0xffffffff, unk71c);
	ram_mask(hwsq, 0x100718, 0xffffffff, unk718);
	ram_mask(hwsq, 0x100710, 0xffffffff, unk710);

	/* XXX: G94 does not even test these regs in trace. Harmless we do it,
	 * but why is it omitted? */
	if (next->bios.rammap_00_16_20) {
		ram_wr32(hwsq, 0x1005a0, next->bios.ramcfg_00_07 << 16 |
					 next->bios.ramcfg_00_06 << 8 |
					 next->bios.ramcfg_00_05);
		ram_wr32(hwsq, 0x1005a4, next->bios.ramcfg_00_09 << 8 |
					 next->bios.ramcfg_00_08);
		ram_mask(hwsq, 0x10053c, 0x00001000, 0x00000000);
	} else {
		ram_mask(hwsq, 0x10053c, 0x00001000, 0x00001000);
	}
	ram_mask(hwsq, mr[1], 0xffffffff, ram->base.mr[1]);

	if (!next->bios.timing_10_ODT)
		nv50_ram_gpio(hwsq, 0x2e, 0);

	/* Reset DLL */
	if (!next->bios.ramcfg_DLLoff)
		nvkm_sddr2_dll_reset(hwsq);

	ram_setf(hwsq, 0x10, 0x01); /* enable fb */
	ram_wait(hwsq, 0x00, 0x00); /* wait for fb enabled */
	ram_wr32(hwsq, 0x611200, 0x00003330);
	ram_wr32(hwsq, 0x002504, 0x00000000); /* un-block fifo */

	if (next->bios.rammap_00_17_02)
		ram_mask(hwsq, 0x100200, 0x00000800, 0x00000800);
	if (!next->bios.rammap_00_16_40)
		ram_mask(hwsq, 0x004008, 0x00004000, 0x00000000);
	if (next->bios.ramcfg_00_03_02)
		ram_mask(hwsq, 0x10021c, 0x00010000, 0x00010000);
	if (subdev->device->chipset <= 0x96 && next->bios.ramcfg_00_03_02)
		ram_mask(hwsq, 0x100710, 0x00000200, 0x00000200);

	return 0;
}