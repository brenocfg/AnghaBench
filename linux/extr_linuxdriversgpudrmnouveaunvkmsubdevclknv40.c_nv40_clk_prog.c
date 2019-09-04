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
struct nvkm_device {int dummy; } ;
struct nvkm_clk {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nv40_clk {int npll_ctrl; int spll; int ctrl; int /*<<< orphan*/  npll_coef; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 struct nv40_clk* nv40_clk (struct nvkm_clk*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv40_clk_prog(struct nvkm_clk *base)
{
	struct nv40_clk *clk = nv40_clk(base);
	struct nvkm_device *device = clk->base.subdev.device;
	nvkm_mask(device, 0x00c040, 0x00000333, 0x00000000);
	nvkm_wr32(device, 0x004004, clk->npll_coef);
	nvkm_mask(device, 0x004000, 0xc0070100, clk->npll_ctrl);
	nvkm_mask(device, 0x004008, 0xc007ffff, clk->spll);
	mdelay(5);
	nvkm_mask(device, 0x00c040, 0x00000333, clk->ctrl);
	return 0;
}