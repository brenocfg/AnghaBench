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
typedef  int u32 ;
struct nvkm_pll_vals {int dummy; } ;
struct nvkm_devinit {int dummy; } ;
struct nvkm_device {TYPE_3__* bios; struct nvkm_devinit* devinit; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct nvkm_clk {TYPE_1__ subdev; } ;
struct TYPE_5__ {int chip; } ;
struct TYPE_6__ {TYPE_2__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  setPLL_double_highregs (struct nvkm_devinit*,int,struct nvkm_pll_vals*) ; 
 int /*<<< orphan*/  setPLL_double_lowregs (struct nvkm_devinit*,int,struct nvkm_pll_vals*) ; 
 int /*<<< orphan*/  setPLL_single (struct nvkm_devinit*,int,struct nvkm_pll_vals*) ; 

int
nv04_clk_pll_prog(struct nvkm_clk *clk, u32 reg1, struct nvkm_pll_vals *pv)
{
	struct nvkm_device *device = clk->subdev.device;
	struct nvkm_devinit *devinit = device->devinit;
	int cv = device->bios->version.chip;

	if (cv == 0x30 || cv == 0x31 || cv == 0x35 || cv == 0x36 ||
	    cv >= 0x40) {
		if (reg1 > 0x405c)
			setPLL_double_highregs(devinit, reg1, pv);
		else
			setPLL_double_lowregs(devinit, reg1, pv);
	} else
		setPLL_single(devinit, reg1, pv);

	return 0;
}