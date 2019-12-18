#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nvkm_subdev {TYPE_4__* device; } ;
struct TYPE_6__ {scalar_t__ max_freq; } ;
struct TYPE_5__ {scalar_t__ max_freq; } ;
struct nvbios_pll {TYPE_2__ vco2; TYPE_1__ vco1; } ;
struct TYPE_7__ {struct nvkm_subdev subdev; } ;
struct nv40_clk {TYPE_3__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  bios; } ;

/* Variables and functions */
 int ERANGE ; 
 int nv04_pll_calc (struct nvkm_subdev*,struct nvbios_pll*,scalar_t__,int*,int*,int*,int*,int*) ; 
 int nvbios_pll_parse (int /*<<< orphan*/ ,scalar_t__,struct nvbios_pll*) ; 

__attribute__((used)) static int
nv40_clk_calc_pll(struct nv40_clk *clk, u32 reg, u32 khz,
		  int *N1, int *M1, int *N2, int *M2, int *log2P)
{
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvbios_pll pll;
	int ret;

	ret = nvbios_pll_parse(subdev->device->bios, reg, &pll);
	if (ret)
		return ret;

	if (khz < pll.vco1.max_freq)
		pll.vco2.max_freq = 0;

	ret = nv04_pll_calc(subdev, &pll, khz, N1, M1, N2, M2, log2P);
	if (ret == 0)
		return -ERANGE;

	return ret;
}