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
struct nvkm_subdev {TYPE_1__* device; } ;
struct nvkm_ram_func {int dummy; } ;
struct nvkm_ram {int dummy; } ;
struct nvkm_fb {struct nvkm_subdev subdev; } ;
struct nvkm_bios {int dummy; } ;
struct TYPE_4__ {void* r_0x13d8f4; void* r_0x611200; void* r_0x61c140; void* r_0x1373f8; void* r_0x1373f0; void* r_0x1373ec; void* r_0x137360; void* r_0x137310; void* r_0x10fb08; void* r_0x10fb04; void* r_0x10f9b4; void* r_0x10f9b0; void* r_0x10f998; void* r_0x10f990; void* r_0x10f98c; void* r_0x10f988; void* r_0x10f830; void* r_0x10f824; void* r_0x10f808; void* r_0x10f800; void* r_0x10f614; void* r_0x10f610; void* r_0x10f314; void* r_0x10f310; void* r_0x10f210; void* r_0x10f200; void* r_0x10f090; void* r_0x10f050; void* r_0x100b0c; void* r_0x10f914; void* r_0x10f910; void* r_0x10f348; void* r_0x10f344; void* r_0x10f340; void* r_0x10f338; void* r_0x10f300; void* r_0x10f2a0; void* r_0x10f29c; void* r_0x10f298; void* r_0x10f294; void* r_0x10f290; void* r_0x137390; void* r_0x132100; void* r_0x132004; void* r_0x132000; void* r_0x137330; void* r_0x137320; void* r_0x10fe24; void* r_0x10fe20; } ;
struct gf100_ram {TYPE_2__ fuc; int /*<<< orphan*/  mempll; int /*<<< orphan*/  refpll; struct nvkm_ram base; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gf100_ram_ctor (struct nvkm_ram_func const*,struct nvkm_fb*,struct nvkm_ram*) ; 
 struct gf100_ram* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvbios_pll_parse (struct nvkm_bios*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 
 void* ramfuc_reg (int) ; 

int
gf100_ram_new_(const struct nvkm_ram_func *func,
	       struct nvkm_fb *fb, struct nvkm_ram **pram)
{
	struct nvkm_subdev *subdev = &fb->subdev;
	struct nvkm_bios *bios = subdev->device->bios;
	struct gf100_ram *ram;
	int ret;

	if (!(ram = kzalloc(sizeof(*ram), GFP_KERNEL)))
		return -ENOMEM;
	*pram = &ram->base;

	ret = gf100_ram_ctor(func, fb, &ram->base);
	if (ret)
		return ret;

	ret = nvbios_pll_parse(bios, 0x0c, &ram->refpll);
	if (ret) {
		nvkm_error(subdev, "mclk refpll data not found\n");
		return ret;
	}

	ret = nvbios_pll_parse(bios, 0x04, &ram->mempll);
	if (ret) {
		nvkm_error(subdev, "mclk pll data not found\n");
		return ret;
	}

	ram->fuc.r_0x10fe20 = ramfuc_reg(0x10fe20);
	ram->fuc.r_0x10fe24 = ramfuc_reg(0x10fe24);
	ram->fuc.r_0x137320 = ramfuc_reg(0x137320);
	ram->fuc.r_0x137330 = ramfuc_reg(0x137330);

	ram->fuc.r_0x132000 = ramfuc_reg(0x132000);
	ram->fuc.r_0x132004 = ramfuc_reg(0x132004);
	ram->fuc.r_0x132100 = ramfuc_reg(0x132100);

	ram->fuc.r_0x137390 = ramfuc_reg(0x137390);

	ram->fuc.r_0x10f290 = ramfuc_reg(0x10f290);
	ram->fuc.r_0x10f294 = ramfuc_reg(0x10f294);
	ram->fuc.r_0x10f298 = ramfuc_reg(0x10f298);
	ram->fuc.r_0x10f29c = ramfuc_reg(0x10f29c);
	ram->fuc.r_0x10f2a0 = ramfuc_reg(0x10f2a0);

	ram->fuc.r_0x10f300 = ramfuc_reg(0x10f300);
	ram->fuc.r_0x10f338 = ramfuc_reg(0x10f338);
	ram->fuc.r_0x10f340 = ramfuc_reg(0x10f340);
	ram->fuc.r_0x10f344 = ramfuc_reg(0x10f344);
	ram->fuc.r_0x10f348 = ramfuc_reg(0x10f348);

	ram->fuc.r_0x10f910 = ramfuc_reg(0x10f910);
	ram->fuc.r_0x10f914 = ramfuc_reg(0x10f914);

	ram->fuc.r_0x100b0c = ramfuc_reg(0x100b0c);
	ram->fuc.r_0x10f050 = ramfuc_reg(0x10f050);
	ram->fuc.r_0x10f090 = ramfuc_reg(0x10f090);
	ram->fuc.r_0x10f200 = ramfuc_reg(0x10f200);
	ram->fuc.r_0x10f210 = ramfuc_reg(0x10f210);
	ram->fuc.r_0x10f310 = ramfuc_reg(0x10f310);
	ram->fuc.r_0x10f314 = ramfuc_reg(0x10f314);
	ram->fuc.r_0x10f610 = ramfuc_reg(0x10f610);
	ram->fuc.r_0x10f614 = ramfuc_reg(0x10f614);
	ram->fuc.r_0x10f800 = ramfuc_reg(0x10f800);
	ram->fuc.r_0x10f808 = ramfuc_reg(0x10f808);
	ram->fuc.r_0x10f824 = ramfuc_reg(0x10f824);
	ram->fuc.r_0x10f830 = ramfuc_reg(0x10f830);
	ram->fuc.r_0x10f988 = ramfuc_reg(0x10f988);
	ram->fuc.r_0x10f98c = ramfuc_reg(0x10f98c);
	ram->fuc.r_0x10f990 = ramfuc_reg(0x10f990);
	ram->fuc.r_0x10f998 = ramfuc_reg(0x10f998);
	ram->fuc.r_0x10f9b0 = ramfuc_reg(0x10f9b0);
	ram->fuc.r_0x10f9b4 = ramfuc_reg(0x10f9b4);
	ram->fuc.r_0x10fb04 = ramfuc_reg(0x10fb04);
	ram->fuc.r_0x10fb08 = ramfuc_reg(0x10fb08);
	ram->fuc.r_0x137310 = ramfuc_reg(0x137300);
	ram->fuc.r_0x137310 = ramfuc_reg(0x137310);
	ram->fuc.r_0x137360 = ramfuc_reg(0x137360);
	ram->fuc.r_0x1373ec = ramfuc_reg(0x1373ec);
	ram->fuc.r_0x1373f0 = ramfuc_reg(0x1373f0);
	ram->fuc.r_0x1373f8 = ramfuc_reg(0x1373f8);

	ram->fuc.r_0x61c140 = ramfuc_reg(0x61c140);
	ram->fuc.r_0x611200 = ramfuc_reg(0x611200);

	ram->fuc.r_0x13d8f4 = ramfuc_reg(0x13d8f4);
	return 0;
}