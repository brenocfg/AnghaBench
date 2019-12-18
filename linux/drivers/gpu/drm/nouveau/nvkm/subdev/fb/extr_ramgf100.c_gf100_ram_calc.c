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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_ram {int dummy; } ;
struct nvkm_device {struct nvkm_bios* bios; struct nvkm_clk* clk; } ;
struct nvkm_clk {int dummy; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_ramcfg {int dummy; } ;
struct gf100_ramfuc {int dummy; } ;
struct TYPE_6__ {int refclk; } ;
struct TYPE_4__ {TYPE_2__* fb; } ;
struct gf100_ram {TYPE_3__ mempll; TYPE_3__ refpll; TYPE_1__ base; struct gf100_ramfuc fuc; } ;
struct TYPE_5__ {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 struct gf100_ram* gf100_ram (struct nvkm_ram*) ; 
 int /*<<< orphan*/  gf100_ram_train (struct gf100_ramfuc*,int) ; 
 int gt215_pll_calc (struct nvkm_subdev*,TYPE_3__*,int,int*,int /*<<< orphan*/ *,int*,int*) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  nv_clk_src_sppll0 ; 
 int /*<<< orphan*/  nv_clk_src_sppll1 ; 
 int nvbios_ramcfg_index (struct nvkm_subdev*) ; 
 int nvbios_rammapEm (struct nvkm_bios*,int,int*,int*,int*,int*,struct nvbios_ramcfg*) ; 
 int nvbios_rd08 (struct nvkm_bios*,int) ; 
 int nvbios_timingEe (struct nvkm_bios*,int,int*,int*,int*,int*) ; 
 int nvkm_clk_read (struct nvkm_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 int ram_init (struct gf100_ramfuc*,TYPE_2__*) ; 
 int /*<<< orphan*/  ram_mask (struct gf100_ramfuc*,int,int,int) ; 
 int /*<<< orphan*/  ram_nsec (struct gf100_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_nuke (struct gf100_ramfuc*,int) ; 
 int ram_rd32 (struct gf100_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_wait (struct gf100_ramfuc*,int,int,int,int) ; 
 int /*<<< orphan*/  ram_wr32 (struct gf100_ramfuc*,int,int) ; 

int
gf100_ram_calc(struct nvkm_ram *base, u32 freq)
{
	struct gf100_ram *ram = gf100_ram(base);
	struct gf100_ramfuc *fuc = &ram->fuc;
	struct nvkm_subdev *subdev = &ram->base.fb->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_clk *clk = device->clk;
	struct nvkm_bios *bios = device->bios;
	struct nvbios_ramcfg cfg;
	u8  ver, cnt, len, strap;
	struct {
		u32 data;
		u8  size;
	} rammap, ramcfg, timing;
	int ref, div, out;
	int from, mode;
	int N1, M1, P;
	int ret;

	/* lookup memory config data relevant to the target frequency */
	rammap.data = nvbios_rammapEm(bios, freq / 1000, &ver, &rammap.size,
				      &cnt, &ramcfg.size, &cfg);
	if (!rammap.data || ver != 0x10 || rammap.size < 0x0e) {
		nvkm_error(subdev, "invalid/missing rammap entry\n");
		return -EINVAL;
	}

	/* locate specific data set for the attached memory */
	strap = nvbios_ramcfg_index(subdev);
	if (strap >= cnt) {
		nvkm_error(subdev, "invalid ramcfg strap\n");
		return -EINVAL;
	}

	ramcfg.data = rammap.data + rammap.size + (strap * ramcfg.size);
	if (!ramcfg.data || ver != 0x10 || ramcfg.size < 0x0e) {
		nvkm_error(subdev, "invalid/missing ramcfg entry\n");
		return -EINVAL;
	}

	/* lookup memory timings, if bios says they're present */
	strap = nvbios_rd08(bios, ramcfg.data + 0x01);
	if (strap != 0xff) {
		timing.data = nvbios_timingEe(bios, strap, &ver, &timing.size,
					      &cnt, &len);
		if (!timing.data || ver != 0x10 || timing.size < 0x19) {
			nvkm_error(subdev, "invalid/missing timing entry\n");
			return -EINVAL;
		}
	} else {
		timing.data = 0;
	}

	ret = ram_init(fuc, ram->base.fb);
	if (ret)
		return ret;

	/* determine current mclk configuration */
	from = !!(ram_rd32(fuc, 0x1373f0) & 0x00000002); /*XXX: ok? */

	/* determine target mclk configuration */
	if (!(ram_rd32(fuc, 0x137300) & 0x00000100))
		ref = nvkm_clk_read(clk, nv_clk_src_sppll0);
	else
		ref = nvkm_clk_read(clk, nv_clk_src_sppll1);
	div = max(min((ref * 2) / freq, (u32)65), (u32)2) - 2;
	out = (ref * 2) / (div + 2);
	mode = freq != out;

	ram_mask(fuc, 0x137360, 0x00000002, 0x00000000);

	if ((ram_rd32(fuc, 0x132000) & 0x00000002) || 0 /*XXX*/) {
		ram_nuke(fuc, 0x132000);
		ram_mask(fuc, 0x132000, 0x00000002, 0x00000002);
		ram_mask(fuc, 0x132000, 0x00000002, 0x00000000);
	}

	if (mode == 1) {
		ram_nuke(fuc, 0x10fe20);
		ram_mask(fuc, 0x10fe20, 0x00000002, 0x00000002);
		ram_mask(fuc, 0x10fe20, 0x00000002, 0x00000000);
	}

// 0x00020034 // 0x0000000a
	ram_wr32(fuc, 0x132100, 0x00000001);

	if (mode == 1 && from == 0) {
		/* calculate refpll */
		ret = gt215_pll_calc(subdev, &ram->refpll, ram->mempll.refclk,
				     &N1, NULL, &M1, &P);
		if (ret <= 0) {
			nvkm_error(subdev, "unable to calc refpll\n");
			return ret ? ret : -ERANGE;
		}

		ram_wr32(fuc, 0x10fe20, 0x20010000);
		ram_wr32(fuc, 0x137320, 0x00000003);
		ram_wr32(fuc, 0x137330, 0x81200006);
		ram_wr32(fuc, 0x10fe24, (P << 16) | (N1 << 8) | M1);
		ram_wr32(fuc, 0x10fe20, 0x20010001);
		ram_wait(fuc, 0x137390, 0x00020000, 0x00020000, 64000);

		/* calculate mempll */
		ret = gt215_pll_calc(subdev, &ram->mempll, freq,
				     &N1, NULL, &M1, &P);
		if (ret <= 0) {
			nvkm_error(subdev, "unable to calc refpll\n");
			return ret ? ret : -ERANGE;
		}

		ram_wr32(fuc, 0x10fe20, 0x20010005);
		ram_wr32(fuc, 0x132004, (P << 16) | (N1 << 8) | M1);
		ram_wr32(fuc, 0x132000, 0x18010101);
		ram_wait(fuc, 0x137390, 0x00000002, 0x00000002, 64000);
	} else
	if (mode == 0) {
		ram_wr32(fuc, 0x137300, 0x00000003);
	}

	if (from == 0) {
		ram_nuke(fuc, 0x10fb04);
		ram_mask(fuc, 0x10fb04, 0x0000ffff, 0x00000000);
		ram_nuke(fuc, 0x10fb08);
		ram_mask(fuc, 0x10fb08, 0x0000ffff, 0x00000000);
		ram_wr32(fuc, 0x10f988, 0x2004ff00);
		ram_wr32(fuc, 0x10f98c, 0x003fc040);
		ram_wr32(fuc, 0x10f990, 0x20012001);
		ram_wr32(fuc, 0x10f998, 0x00011a00);
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
	} else {
		ram_wr32(fuc, 0x10f988, 0x20010000);
		ram_wr32(fuc, 0x10f98c, 0x00000000);
		ram_wr32(fuc, 0x10f990, 0x20012001);
		ram_wr32(fuc, 0x10f998, 0x00010a00);
	}

	if (from == 0) {
// 0x00020039 // 0x000000ba
	}

// 0x0002003a // 0x00000002
	ram_wr32(fuc, 0x100b0c, 0x00080012);
// 0x00030014 // 0x00000000 // 0x02b5f070
// 0x00030014 // 0x00010000 // 0x02b5f070
	ram_wr32(fuc, 0x611200, 0x00003300);
// 0x00020034 // 0x0000000a
// 0x00030020 // 0x00000001 // 0x00000000

	ram_mask(fuc, 0x10f200, 0x00000800, 0x00000000);
	ram_wr32(fuc, 0x10f210, 0x00000000);
	ram_nsec(fuc, 1000);
	if (mode == 0)
		gf100_ram_train(fuc, 0x000c1001);
	ram_wr32(fuc, 0x10f310, 0x00000001);
	ram_nsec(fuc, 1000);
	ram_wr32(fuc, 0x10f090, 0x00000061);
	ram_wr32(fuc, 0x10f090, 0xc000007f);
	ram_nsec(fuc, 1000);

	if (from == 0) {
		ram_wr32(fuc, 0x10f824, 0x00007fd4);
	} else {
		ram_wr32(fuc, 0x1373ec, 0x00020404);
	}

	if (mode == 0) {
		ram_mask(fuc, 0x10f808, 0x00080000, 0x00000000);
		ram_mask(fuc, 0x10f200, 0x00008000, 0x00008000);
		ram_wr32(fuc, 0x10f830, 0x41500010);
		ram_mask(fuc, 0x10f830, 0x01000000, 0x00000000);
		ram_mask(fuc, 0x132100, 0x00000100, 0x00000100);
		ram_wr32(fuc, 0x10f050, 0xff000090);
		ram_wr32(fuc, 0x1373ec, 0x00020f0f);
		ram_wr32(fuc, 0x1373f0, 0x00000003);
		ram_wr32(fuc, 0x137310, 0x81201616);
		ram_wr32(fuc, 0x132100, 0x00000001);
// 0x00020039 // 0x000000ba
		ram_wr32(fuc, 0x10f830, 0x00300017);
		ram_wr32(fuc, 0x1373f0, 0x00000001);
		ram_wr32(fuc, 0x10f824, 0x00007e77);
		ram_wr32(fuc, 0x132000, 0x18030001);
		ram_wr32(fuc, 0x10f090, 0x4000007e);
		ram_nsec(fuc, 2000);
		ram_wr32(fuc, 0x10f314, 0x00000001);
		ram_wr32(fuc, 0x10f210, 0x80000000);
		ram_wr32(fuc, 0x10f338, 0x00300220);
		ram_wr32(fuc, 0x10f300, 0x0000011d);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f290, 0x02060505);
		ram_wr32(fuc, 0x10f294, 0x34208288);
		ram_wr32(fuc, 0x10f298, 0x44050411);
		ram_wr32(fuc, 0x10f29c, 0x0000114c);
		ram_wr32(fuc, 0x10f2a0, 0x42e10069);
		ram_wr32(fuc, 0x10f614, 0x40044f77);
		ram_wr32(fuc, 0x10f610, 0x40044f77);
		ram_wr32(fuc, 0x10f344, 0x00600009);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f348, 0x00700008);
		ram_wr32(fuc, 0x61c140, 0x19240000);
		ram_wr32(fuc, 0x10f830, 0x00300017);
		gf100_ram_train(fuc, 0x80021001);
		gf100_ram_train(fuc, 0x80081001);
		ram_wr32(fuc, 0x10f340, 0x00500004);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f830, 0x01300017);
		ram_wr32(fuc, 0x10f830, 0x00300017);
// 0x00030020 // 0x00000000 // 0x00000000
// 0x00020034 // 0x0000000b
		ram_wr32(fuc, 0x100b0c, 0x00080028);
		ram_wr32(fuc, 0x611200, 0x00003330);
	} else {
		ram_wr32(fuc, 0x10f800, 0x00001800);
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
		ram_wr32(fuc, 0x1373ec, 0x00020404);
		ram_wr32(fuc, 0x1373f0, 0x00000003);
		ram_wr32(fuc, 0x10f830, 0x40700010);
		ram_wr32(fuc, 0x10f830, 0x40500010);
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
		ram_wr32(fuc, 0x1373f8, 0x00000000);
		ram_wr32(fuc, 0x132100, 0x00000101);
		ram_wr32(fuc, 0x137310, 0x89201616);
		ram_wr32(fuc, 0x10f050, 0xff000090);
		ram_wr32(fuc, 0x1373ec, 0x00030404);
		ram_wr32(fuc, 0x1373f0, 0x00000002);
	// 0x00020039 // 0x00000011
		ram_wr32(fuc, 0x132100, 0x00000001);
		ram_wr32(fuc, 0x1373f8, 0x00002000);
		ram_nsec(fuc, 2000);
		ram_wr32(fuc, 0x10f808, 0x7aaa0050);
		ram_wr32(fuc, 0x10f830, 0x00500010);
		ram_wr32(fuc, 0x10f200, 0x00ce1000);
		ram_wr32(fuc, 0x10f090, 0x4000007e);
		ram_nsec(fuc, 2000);
		ram_wr32(fuc, 0x10f314, 0x00000001);
		ram_wr32(fuc, 0x10f210, 0x80000000);
		ram_wr32(fuc, 0x10f338, 0x00300200);
		ram_wr32(fuc, 0x10f300, 0x0000084d);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f290, 0x0b343825);
		ram_wr32(fuc, 0x10f294, 0x3483028e);
		ram_wr32(fuc, 0x10f298, 0x440c0600);
		ram_wr32(fuc, 0x10f29c, 0x0000214c);
		ram_wr32(fuc, 0x10f2a0, 0x42e20069);
		ram_wr32(fuc, 0x10f200, 0x00ce0000);
		ram_wr32(fuc, 0x10f614, 0x60044e77);
		ram_wr32(fuc, 0x10f610, 0x60044e77);
		ram_wr32(fuc, 0x10f340, 0x00500000);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f344, 0x00600228);
		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f348, 0x00700000);
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
		ram_wr32(fuc, 0x61c140, 0x09a40000);

		gf100_ram_train(fuc, 0x800e1008);

		ram_nsec(fuc, 1000);
		ram_wr32(fuc, 0x10f800, 0x00001804);
	// 0x00030020 // 0x00000000 // 0x00000000
	// 0x00020034 // 0x0000000b
		ram_wr32(fuc, 0x13d8f4, 0x00000000);
		ram_wr32(fuc, 0x100b0c, 0x00080028);
		ram_wr32(fuc, 0x611200, 0x00003330);
		ram_nsec(fuc, 100000);
		ram_wr32(fuc, 0x10f9b0, 0x05313f41);
		ram_wr32(fuc, 0x10f9b4, 0x00002f50);

		gf100_ram_train(fuc, 0x010c1001);
	}

	ram_mask(fuc, 0x10f200, 0x00000800, 0x00000800);
// 0x00020016 // 0x00000000

	if (mode == 0)
		ram_mask(fuc, 0x132000, 0x00000001, 0x00000000);

	return 0;
}