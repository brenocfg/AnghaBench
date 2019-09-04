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
struct gf100_clk_info {int /*<<< orphan*/  dsrc; int /*<<< orphan*/  ddiv; int /*<<< orphan*/  ssel; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct gf100_clk {TYPE_2__ base; struct gf100_clk_info* eng; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gf100_clk_prog_0(struct gf100_clk *clk, int idx)
{
	struct gf100_clk_info *info = &clk->eng[idx];
	struct nvkm_device *device = clk->base.subdev.device;
	if (idx < 7 && !info->ssel) {
		nvkm_mask(device, 0x1371d0 + (idx * 0x04), 0x80003f3f, info->ddiv);
		nvkm_wr32(device, 0x137160 + (idx * 0x04), info->dsrc);
	}
}