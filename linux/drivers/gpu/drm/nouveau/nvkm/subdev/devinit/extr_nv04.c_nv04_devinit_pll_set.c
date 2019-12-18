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
typedef  int u32 ;
struct nvkm_subdev {TYPE_1__* device; } ;
struct nvkm_pll_vals {int N1; int M1; int N2; int M2; int log2P; int /*<<< orphan*/  refclk; } ;
struct nvkm_devinit {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {int chip; } ;
struct nvkm_bios {TYPE_2__ version; } ;
struct nvbios_pll {int /*<<< orphan*/  refclk; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int EINVAL ; 
 int nv04_pll_calc (struct nvkm_subdev*,struct nvbios_pll*,int,int*,int*,int*,int*,int*) ; 
 int nvbios_pll_parse (struct nvkm_bios*,int,struct nvbios_pll*) ; 
 int /*<<< orphan*/  setPLL_double_highregs (struct nvkm_devinit*,int,struct nvkm_pll_vals*) ; 
 int /*<<< orphan*/  setPLL_double_lowregs (struct nvkm_devinit*,int,struct nvkm_pll_vals*) ; 
 int /*<<< orphan*/  setPLL_single (struct nvkm_devinit*,int,struct nvkm_pll_vals*) ; 

int
nv04_devinit_pll_set(struct nvkm_devinit *devinit, u32 type, u32 freq)
{
	struct nvkm_subdev *subdev = &devinit->subdev;
	struct nvkm_bios *bios = subdev->device->bios;
	struct nvkm_pll_vals pv;
	struct nvbios_pll info;
	int cv = bios->version.chip;
	int N1, M1, N2, M2, P;
	int ret;

	ret = nvbios_pll_parse(bios, type > 0x405c ? type : type - 4, &info);
	if (ret)
		return ret;

	ret = nv04_pll_calc(subdev, &info, freq, &N1, &M1, &N2, &M2, &P);
	if (!ret)
		return -EINVAL;

	pv.refclk = info.refclk;
	pv.N1 = N1;
	pv.M1 = M1;
	pv.N2 = N2;
	pv.M2 = M2;
	pv.log2P = P;

	if (cv == 0x30 || cv == 0x31 || cv == 0x35 || cv == 0x36 ||
	    cv >= 0x40) {
		if (type > 0x405c)
			setPLL_double_highregs(devinit, type, &pv);
		else
			setPLL_double_lowregs(devinit, type, &pv);
	} else
		setPLL_single(devinit, type, &pv);

	return 0;
}