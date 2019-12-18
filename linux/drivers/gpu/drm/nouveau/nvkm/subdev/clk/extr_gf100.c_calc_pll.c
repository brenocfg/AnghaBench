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
struct nvkm_subdev {TYPE_2__* device; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_pll {int /*<<< orphan*/  refclk; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct gf100_clk {TYPE_1__ base; } ;
struct TYPE_4__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int gt215_pll_calc (struct nvkm_subdev*,struct nvbios_pll*,int,int*,int /*<<< orphan*/ *,int*,int*) ; 
 int nvbios_pll_parse (struct nvkm_bios*,int,struct nvbios_pll*) ; 
 int /*<<< orphan*/  read_div (struct gf100_clk*,int,int,int) ; 

__attribute__((used)) static u32
calc_pll(struct gf100_clk *clk, int idx, u32 freq, u32 *coef)
{
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_bios *bios = subdev->device->bios;
	struct nvbios_pll limits;
	int N, M, P, ret;

	ret = nvbios_pll_parse(bios, 0x137000 + (idx * 0x20), &limits);
	if (ret)
		return 0;

	limits.refclk = read_div(clk, idx, 0x137120, 0x137140);
	if (!limits.refclk)
		return 0;

	ret = gt215_pll_calc(subdev, &limits, freq, &N, NULL, &M, &P);
	if (ret <= 0)
		return 0;

	*coef = (P << 16) | (N << 8) | M;
	return ret;
}