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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_subdev {TYPE_3__* device; } ;
struct nvkm_ram {int dummy; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_pll {scalar_t__ max_p; scalar_t__ bias_p; } ;
struct TYPE_5__ {TYPE_1__* fb; } ;
struct nv40_ram {int ctrl; int coef; TYPE_2__ base; } ;
struct TYPE_6__ {struct nvkm_bios* bios; } ;
struct TYPE_4__ {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int min (scalar_t__,int) ; 
 int nv04_pll_calc (struct nvkm_subdev*,struct nvbios_pll*,int /*<<< orphan*/ ,int*,int*,int*,int*,int*) ; 
 struct nv40_ram* nv40_ram (struct nvkm_ram*) ; 
 int nvbios_pll_parse (struct nvkm_bios*,int,struct nvbios_pll*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*) ; 

__attribute__((used)) static int
nv40_ram_calc(struct nvkm_ram *base, u32 freq)
{
	struct nv40_ram *ram = nv40_ram(base);
	struct nvkm_subdev *subdev = &ram->base.fb->subdev;
	struct nvkm_bios *bios = subdev->device->bios;
	struct nvbios_pll pll;
	int N1, M1, N2, M2;
	int log2P, ret;

	ret = nvbios_pll_parse(bios, 0x04, &pll);
	if (ret) {
		nvkm_error(subdev, "mclk pll data not found\n");
		return ret;
	}

	ret = nv04_pll_calc(subdev, &pll, freq, &N1, &M1, &N2, &M2, &log2P);
	if (ret < 0)
		return ret;

	ram->ctrl  = 0x80000000 | (log2P << 16);
	ram->ctrl |= min(pll.bias_p + log2P, (int)pll.max_p) << 20;
	if (N2 == M2) {
		ram->ctrl |= 0x00000100;
		ram->coef  = (N1 << 8) | M1;
	} else {
		ram->ctrl |= 0x40000000;
		ram->coef  = (N2 << 24) | (M2 << 16) | (N1 << 8) | M1;
	}

	return 0;
}