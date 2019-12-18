#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int ramcfg_11_03_c0; int ramcfg_11_03_30; int rammap_11_11_0c; int ramcfg_11_09; int ramcfg_11_04; int* timing; int ramcfg_11_02_03; int timing_20_30_07; int ramcfg_11_03_0f; int timing_20_2c_003f; int timing_20_2c_1fc0; int timing_20_30_f8; int timing_20_31_0800; int timing_20_31_0780; int timing_20_31_0078; int timing_20_31_0007; int timing_20_31_8000; int timing_20_31_7000; scalar_t__ rammap_11_08_01; scalar_t__ ramcfg_11_07_02; int /*<<< orphan*/  rammap_11_08_10; scalar_t__ ramcfg_11_07_04; scalar_t__ ramcfg_11_07_08; scalar_t__ ramcfg_11_08_10; scalar_t__ ramcfg_11_01_01; scalar_t__ ramcfg_11_01_10; int /*<<< orphan*/  ramcfg_11_07_80; scalar_t__ rammap_11_08_0c; scalar_t__ ramcfg_11_03_f0; int /*<<< orphan*/  ramcfg_11_01_04; scalar_t__ ramcfg_11_01_02; scalar_t__ ramcfg_11_08_20; scalar_t__ ramcfg_11_08_02; scalar_t__ ramcfg_11_08_04; scalar_t__ ramcfg_11_08_08; scalar_t__ ramcfg_11_08_01; scalar_t__ ramcfg_11_01_08; scalar_t__ ramcfg_11_07_10; scalar_t__ ramcfg_11_02_40; scalar_t__ ramcfg_11_02_80; scalar_t__ ramcfg_11_07_40; int /*<<< orphan*/  ramcfg_11_02_04; int /*<<< orphan*/  ramcfg_11_02_08; } ;
struct nvkm_ram_data {TYPE_5__ bios; } ;
struct gk104_ramfuc {int* r_func2E; int* r_funcMV; } ;
struct TYPE_9__ {int* mr; int mr1_nuts; TYPE_3__* fb; struct nvkm_ram_data* next; } ;
struct TYPE_6__ {scalar_t__ ramcfg_11_01_10; scalar_t__ ramcfg_11_02_03; scalar_t__ ramcfg_11_01_02; scalar_t__ timing_20_30_07; scalar_t__ ramcfg_11_01_01; scalar_t__ ramcfg_11_08_20; } ;
struct gk104_ram {int from; int mode; TYPE_4__ base; TYPE_1__ diff; struct gk104_ramfuc fuc; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {TYPE_2__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_ENGINE_DISP ; 
 int /*<<< orphan*/  gk104_ram_train (struct gk104_ramfuc*,int,int) ; 
 int gpio2E ; 
 int gpioMV ; 
 int gpiotrig ; 
 int* mr ; 
 scalar_t__ nvkm_device_engine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r1373f4_fini (struct gk104_ramfuc*) ; 
 int /*<<< orphan*/  r1373f4_init (struct gk104_ramfuc*) ; 
 int /*<<< orphan*/  ram_block (struct gk104_ramfuc*) ; 
 scalar_t__ ram_have (struct gk104_ramfuc*,int) ; 
 int ram_mask (struct gk104_ramfuc*,int,int,int) ; 
 int /*<<< orphan*/  ram_nsec (struct gk104_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_nuke (struct gk104_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_nuts (struct gk104_ram*,int,int,int,int) ; 
 int ram_rd32 (struct gk104_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_unblock (struct gk104_ramfuc*) ; 
 int /*<<< orphan*/  ram_wait (struct gk104_ramfuc*,int,int,int,int) ; 
 int /*<<< orphan*/  ram_wr32 (struct gk104_ramfuc*,int,int) ; 

__attribute__((used)) static int
gk104_ram_calc_gddr5(struct gk104_ram *ram, u32 freq)
{
	struct gk104_ramfuc *fuc = &ram->fuc;
	struct nvkm_ram_data *next = ram->base.next;
	int vc = !next->bios.ramcfg_11_02_08;
	int mv = !next->bios.ramcfg_11_02_04;
	u32 mask, data;

	ram_mask(fuc, 0x10f808, 0x40000000, 0x40000000);
	ram_block(fuc);

	if (nvkm_device_engine(ram->base.fb->subdev.device, NVKM_ENGINE_DISP))
		ram_wr32(fuc, 0x62c000, 0x0f0f0000);

	/* MR1: turn termination on early, for some reason.. */
	if ((ram->base.mr[1] & 0x03c) != 0x030) {
		ram_mask(fuc, mr[1], 0x03c, ram->base.mr[1] & 0x03c);
		ram_nuts(ram, mr[1], 0x03c, ram->base.mr1_nuts & 0x03c, 0x000);
	}

	if (vc == 1 && ram_have(fuc, gpio2E)) {
		u32 temp  = ram_mask(fuc, gpio2E, 0x3000, fuc->r_func2E[1]);
		if (temp != ram_rd32(fuc, gpio2E)) {
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 20000);
		}
	}

	ram_mask(fuc, 0x10f200, 0x00000800, 0x00000000);

	gk104_ram_train(fuc, 0x01020000, 0x000c0000);

	ram_wr32(fuc, 0x10f210, 0x00000000); /* REFRESH_AUTO = 0 */
	ram_nsec(fuc, 1000);
	ram_wr32(fuc, 0x10f310, 0x00000001); /* REFRESH */
	ram_nsec(fuc, 1000);

	ram_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	ram_wr32(fuc, 0x10f314, 0x00000001); /* PRECHARGE */
	ram_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	ram_wr32(fuc, 0x10f090, 0x00000061);
	ram_wr32(fuc, 0x10f090, 0xc000007f);
	ram_nsec(fuc, 1000);

	ram_wr32(fuc, 0x10f698, 0x00000000);
	ram_wr32(fuc, 0x10f69c, 0x00000000);

	/*XXX: there does appear to be some kind of condition here, simply
	 *     modifying these bits in the vbios from the default pl0
	 *     entries shows no change.  however, the data does appear to
	 *     be correct and may be required for the transition back
	 */
	mask = 0x800f07e0;
	data = 0x00030000;
	if (ram_rd32(fuc, 0x10f978) & 0x00800000)
		data |= 0x00040000;

	if (1) {
		data |= 0x800807e0;
		switch (next->bios.ramcfg_11_03_c0) {
		case 3: data &= ~0x00000040; break;
		case 2: data &= ~0x00000100; break;
		case 1: data &= ~0x80000000; break;
		case 0: data &= ~0x00000400; break;
		}

		switch (next->bios.ramcfg_11_03_30) {
		case 3: data &= ~0x00000020; break;
		case 2: data &= ~0x00000080; break;
		case 1: data &= ~0x00080000; break;
		case 0: data &= ~0x00000200; break;
		}
	}

	if (next->bios.ramcfg_11_02_80)
		mask |= 0x03000000;
	if (next->bios.ramcfg_11_02_40)
		mask |= 0x00002000;
	if (next->bios.ramcfg_11_07_10)
		mask |= 0x00004000;
	if (next->bios.ramcfg_11_07_08)
		mask |= 0x00000003;
	else {
		mask |= 0x34000000;
		if (ram_rd32(fuc, 0x10f978) & 0x00800000)
			mask |= 0x40000000;
	}
	ram_mask(fuc, 0x10f824, mask, data);

	ram_mask(fuc, 0x132040, 0x00010000, 0x00000000);

	if (ram->from == 2 && ram->mode != 2) {
		ram_mask(fuc, 0x10f808, 0x00080000, 0x00000000);
		ram_mask(fuc, 0x10f200, 0x18008000, 0x00008000);
		ram_mask(fuc, 0x10f800, 0x00000000, 0x00000004);
		ram_mask(fuc, 0x10f830, 0x00008000, 0x01040010);
		ram_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
		r1373f4_init(fuc);
		ram_mask(fuc, 0x1373f0, 0x00000002, 0x00000001);
		r1373f4_fini(fuc);
		ram_mask(fuc, 0x10f830, 0x00c00000, 0x00240001);
	} else
	if (ram->from != 2 && ram->mode != 2) {
		r1373f4_init(fuc);
		r1373f4_fini(fuc);
	}

	if (ram_have(fuc, gpioMV)) {
		u32 temp  = ram_mask(fuc, gpioMV, 0x3000, fuc->r_funcMV[mv]);
		if (temp != ram_rd32(fuc, gpioMV)) {
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 64000);
		}
	}

	if (next->bios.ramcfg_11_02_40 ||
	    next->bios.ramcfg_11_07_10) {
		ram_mask(fuc, 0x132040, 0x00010000, 0x00010000);
		ram_nsec(fuc, 20000);
	}

	if (ram->from != 2 && ram->mode == 2) {
		if (0 /*XXX: Titan */)
			ram_mask(fuc, 0x10f200, 0x18000000, 0x18000000);
		ram_mask(fuc, 0x10f800, 0x00000004, 0x00000000);
		ram_mask(fuc, 0x1373f0, 0x00000000, 0x00000002);
		ram_mask(fuc, 0x10f830, 0x00800001, 0x00408010);
		r1373f4_init(fuc);
		r1373f4_fini(fuc);
		ram_mask(fuc, 0x10f808, 0x00000000, 0x00080000);
		ram_mask(fuc, 0x10f200, 0x00808000, 0x00800000);
	} else
	if (ram->from == 2 && ram->mode == 2) {
		ram_mask(fuc, 0x10f800, 0x00000004, 0x00000000);
		r1373f4_init(fuc);
		r1373f4_fini(fuc);
	}

	if (ram->mode != 2) /*XXX*/ {
		if (next->bios.ramcfg_11_07_40)
			ram_mask(fuc, 0x10f670, 0x80000000, 0x80000000);
	}

	ram_wr32(fuc, 0x10f65c, 0x00000011 * next->bios.rammap_11_11_0c);
	ram_wr32(fuc, 0x10f6b8, 0x01010101 * next->bios.ramcfg_11_09);
	ram_wr32(fuc, 0x10f6bc, 0x01010101 * next->bios.ramcfg_11_09);

	if (!next->bios.ramcfg_11_07_08 && !next->bios.ramcfg_11_07_04) {
		ram_wr32(fuc, 0x10f698, 0x01010101 * next->bios.ramcfg_11_04);
		ram_wr32(fuc, 0x10f69c, 0x01010101 * next->bios.ramcfg_11_04);
	} else
	if (!next->bios.ramcfg_11_07_08) {
		ram_wr32(fuc, 0x10f698, 0x00000000);
		ram_wr32(fuc, 0x10f69c, 0x00000000);
	}

	if (ram->mode != 2) {
		u32 data = 0x01000100 * next->bios.ramcfg_11_04;
		ram_nuke(fuc, 0x10f694);
		ram_mask(fuc, 0x10f694, 0xff00ff00, data);
	}

	if (ram->mode == 2 && next->bios.ramcfg_11_08_10)
		data = 0x00000080;
	else
		data = 0x00000000;
	ram_mask(fuc, 0x10f60c, 0x00000080, data);

	mask = 0x00070000;
	data = 0x00000000;
	if (!next->bios.ramcfg_11_02_80)
		data |= 0x03000000;
	if (!next->bios.ramcfg_11_02_40)
		data |= 0x00002000;
	if (!next->bios.ramcfg_11_07_10)
		data |= 0x00004000;
	if (!next->bios.ramcfg_11_07_08)
		data |= 0x00000003;
	else
		data |= 0x74000000;
	ram_mask(fuc, 0x10f824, mask, data);

	if (next->bios.ramcfg_11_01_08)
		data = 0x00000000;
	else
		data = 0x00001000;
	ram_mask(fuc, 0x10f200, 0x00001000, data);

	if (ram_rd32(fuc, 0x10f670) & 0x80000000) {
		ram_nsec(fuc, 10000);
		ram_mask(fuc, 0x10f670, 0x80000000, 0x00000000);
	}

	if (next->bios.ramcfg_11_08_01)
		data = 0x00100000;
	else
		data = 0x00000000;
	ram_mask(fuc, 0x10f82c, 0x00100000, data);

	data = 0x00000000;
	if (next->bios.ramcfg_11_08_08)
		data |= 0x00002000;
	if (next->bios.ramcfg_11_08_04)
		data |= 0x00001000;
	if (next->bios.ramcfg_11_08_02)
		data |= 0x00004000;
	ram_mask(fuc, 0x10f830, 0x00007000, data);

	/* PFB timing */
	ram_mask(fuc, 0x10f248, 0xffffffff, next->bios.timing[10]);
	ram_mask(fuc, 0x10f290, 0xffffffff, next->bios.timing[0]);
	ram_mask(fuc, 0x10f294, 0xffffffff, next->bios.timing[1]);
	ram_mask(fuc, 0x10f298, 0xffffffff, next->bios.timing[2]);
	ram_mask(fuc, 0x10f29c, 0xffffffff, next->bios.timing[3]);
	ram_mask(fuc, 0x10f2a0, 0xffffffff, next->bios.timing[4]);
	ram_mask(fuc, 0x10f2a4, 0xffffffff, next->bios.timing[5]);
	ram_mask(fuc, 0x10f2a8, 0xffffffff, next->bios.timing[6]);
	ram_mask(fuc, 0x10f2ac, 0xffffffff, next->bios.timing[7]);
	ram_mask(fuc, 0x10f2cc, 0xffffffff, next->bios.timing[8]);
	ram_mask(fuc, 0x10f2e8, 0xffffffff, next->bios.timing[9]);

	data = mask = 0x00000000;
	if (ram->diff.ramcfg_11_08_20) {
		if (next->bios.ramcfg_11_08_20)
			data |= 0x01000000;
		mask |= 0x01000000;
	}
	ram_mask(fuc, 0x10f200, mask, data);

	data = mask = 0x00000000;
	if (ram->diff.ramcfg_11_02_03) {
		data |= next->bios.ramcfg_11_02_03 << 8;
		mask |= 0x00000300;
	}
	if (ram->diff.ramcfg_11_01_10) {
		if (next->bios.ramcfg_11_01_10)
			data |= 0x70000000;
		mask |= 0x70000000;
	}
	ram_mask(fuc, 0x10f604, mask, data);

	data = mask = 0x00000000;
	if (ram->diff.timing_20_30_07) {
		data |= next->bios.timing_20_30_07 << 28;
		mask |= 0x70000000;
	}
	if (ram->diff.ramcfg_11_01_01) {
		if (next->bios.ramcfg_11_01_01)
			data |= 0x00000100;
		mask |= 0x00000100;
	}
	ram_mask(fuc, 0x10f614, mask, data);

	data = mask = 0x00000000;
	if (ram->diff.timing_20_30_07) {
		data |= next->bios.timing_20_30_07 << 28;
		mask |= 0x70000000;
	}
	if (ram->diff.ramcfg_11_01_02) {
		if (next->bios.ramcfg_11_01_02)
			data |= 0x00000100;
		mask |= 0x00000100;
	}
	ram_mask(fuc, 0x10f610, mask, data);

	mask = 0x33f00000;
	data = 0x00000000;
	if (!next->bios.ramcfg_11_01_04)
		data |= 0x20200000;
	if (!next->bios.ramcfg_11_07_80)
		data |= 0x12800000;
	/*XXX: see note above about there probably being some condition
	 *     for the 10f824 stuff that uses ramcfg 3...
	 */
	if (next->bios.ramcfg_11_03_f0) {
		if (next->bios.rammap_11_08_0c) {
			if (!next->bios.ramcfg_11_07_80)
				mask |= 0x00000020;
			else
				data |= 0x00000020;
			mask |= 0x00000004;
		}
	} else {
		mask |= 0x40000020;
		data |= 0x00000004;
	}

	ram_mask(fuc, 0x10f808, mask, data);

	ram_wr32(fuc, 0x10f870, 0x11111111 * next->bios.ramcfg_11_03_0f);

	data = mask = 0x00000000;
	if (ram->diff.ramcfg_11_02_03) {
		data |= next->bios.ramcfg_11_02_03;
		mask |= 0x00000003;
	}
	if (ram->diff.ramcfg_11_01_10) {
		if (next->bios.ramcfg_11_01_10)
			data |= 0x00000004;
		mask |= 0x00000004;
	}

	if ((ram_mask(fuc, 0x100770, mask, data) & mask & 4) != (data & 4)) {
		ram_mask(fuc, 0x100750, 0x00000008, 0x00000008);
		ram_wr32(fuc, 0x100710, 0x00000000);
		ram_wait(fuc, 0x100710, 0x80000000, 0x80000000, 200000);
	}

	data = next->bios.timing_20_30_07 << 8;
	if (next->bios.ramcfg_11_01_01)
		data |= 0x80000000;
	ram_mask(fuc, 0x100778, 0x00000700, data);

	ram_mask(fuc, 0x10f250, 0x000003f0, next->bios.timing_20_2c_003f << 4);
	data = (next->bios.timing[10] & 0x7f000000) >> 24;
	if (data < next->bios.timing_20_2c_1fc0)
		data = next->bios.timing_20_2c_1fc0;
	ram_mask(fuc, 0x10f24c, 0x7f000000, data << 24);
	ram_mask(fuc, 0x10f224, 0x001f0000, next->bios.timing_20_30_f8 << 16);

	ram_mask(fuc, 0x10fec4, 0x041e0f07, next->bios.timing_20_31_0800 << 26 |
					    next->bios.timing_20_31_0780 << 17 |
					    next->bios.timing_20_31_0078 << 8 |
					    next->bios.timing_20_31_0007);
	ram_mask(fuc, 0x10fec8, 0x00000027, next->bios.timing_20_31_8000 << 5 |
					    next->bios.timing_20_31_7000);

	ram_wr32(fuc, 0x10f090, 0x4000007e);
	ram_nsec(fuc, 2000);
	ram_wr32(fuc, 0x10f314, 0x00000001); /* PRECHARGE */
	ram_wr32(fuc, 0x10f310, 0x00000001); /* REFRESH */
	ram_wr32(fuc, 0x10f210, 0x80000000); /* REFRESH_AUTO = 1 */

	if (next->bios.ramcfg_11_08_10 && (ram->mode == 2) /*XXX*/) {
		u32 temp = ram_mask(fuc, 0x10f294, 0xff000000, 0x24000000);
		gk104_ram_train(fuc, 0xbc0e0000, 0xa4010000); /*XXX*/
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f294, temp);
	}

	ram_mask(fuc, mr[3], 0xfff, ram->base.mr[3]);
	ram_wr32(fuc, mr[0], ram->base.mr[0]);
	ram_mask(fuc, mr[8], 0xfff, ram->base.mr[8]);
	ram_nsec(fuc, 1000);
	ram_mask(fuc, mr[1], 0xfff, ram->base.mr[1]);
	ram_mask(fuc, mr[5], 0xfff, ram->base.mr[5] & ~0x004); /* LP3 later */
	ram_mask(fuc, mr[6], 0xfff, ram->base.mr[6]);
	ram_mask(fuc, mr[7], 0xfff, ram->base.mr[7]);

	if (vc == 0 && ram_have(fuc, gpio2E)) {
		u32 temp  = ram_mask(fuc, gpio2E, 0x3000, fuc->r_func2E[0]);
		if (temp != ram_rd32(fuc, gpio2E)) {
			ram_wr32(fuc, gpiotrig, 1);
			ram_nsec(fuc, 20000);
		}
	}

	ram_mask(fuc, 0x10f200, 0x80000000, 0x80000000);
	ram_wr32(fuc, 0x10f318, 0x00000001); /* NOP? */
	ram_mask(fuc, 0x10f200, 0x80000000, 0x00000000);
	ram_nsec(fuc, 1000);
	ram_nuts(ram, 0x10f200, 0x18808800, 0x00000000, 0x18808800);

	data  = ram_rd32(fuc, 0x10f978);
	data &= ~0x00046144;
	data |=  0x0000000b;
	if (!next->bios.ramcfg_11_07_08) {
		if (!next->bios.ramcfg_11_07_04)
			data |= 0x0000200c;
		else
			data |= 0x00000000;
	} else {
		data |= 0x00040044;
	}
	ram_wr32(fuc, 0x10f978, data);

	if (ram->mode == 1) {
		data = ram_rd32(fuc, 0x10f830) | 0x00000001;
		ram_wr32(fuc, 0x10f830, data);
	}

	if (!next->bios.ramcfg_11_07_08) {
		data = 0x88020000;
		if ( next->bios.ramcfg_11_07_04)
			data |= 0x10000000;
		if (!next->bios.rammap_11_08_10)
			data |= 0x00080000;
	} else {
		data = 0xa40e0000;
	}
	gk104_ram_train(fuc, 0xbc0f0000, data);
	if (1) /* XXX: not always? */
		ram_nsec(fuc, 1000);

	if (ram->mode == 2) { /*XXX*/
		ram_mask(fuc, 0x10f800, 0x00000004, 0x00000004);
	}

	/* LP3 */
	if (ram_mask(fuc, mr[5], 0x004, ram->base.mr[5]) != ram->base.mr[5])
		ram_nsec(fuc, 1000);

	if (ram->mode != 2) {
		ram_mask(fuc, 0x10f830, 0x01000000, 0x01000000);
		ram_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
	}

	if (next->bios.ramcfg_11_07_02)
		gk104_ram_train(fuc, 0x80020000, 0x01000000);

	ram_unblock(fuc);

	if (nvkm_device_engine(ram->base.fb->subdev.device, NVKM_ENGINE_DISP))
		ram_wr32(fuc, 0x62c000, 0x0f0f0f00);

	if (next->bios.rammap_11_08_01)
		data = 0x00000800;
	else
		data = 0x00000000;
	ram_mask(fuc, 0x10f200, 0x00000800, data);
	ram_nuts(ram, 0x10f200, 0x18808800, data, 0x18808800);
	return 0;
}