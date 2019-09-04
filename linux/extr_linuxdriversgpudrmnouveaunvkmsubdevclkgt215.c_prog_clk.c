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
struct gt215_clk_info {int clk; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct gt215_clk {TYPE_2__ base; struct gt215_clk_info* eng; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 

__attribute__((used)) static void
prog_clk(struct gt215_clk *clk, int idx, int dom)
{
	struct gt215_clk_info *info = &clk->eng[dom];
	struct nvkm_device *device = clk->base.subdev.device;
	nvkm_mask(device, 0x004120 + (idx * 4), 0x003f3141, 0x00000101 | info->clk);
}