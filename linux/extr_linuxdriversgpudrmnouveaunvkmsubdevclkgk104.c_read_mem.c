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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct gk104_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  read_pll (struct gk104_clk*,int) ; 

__attribute__((used)) static u32
read_mem(struct gk104_clk *clk)
{
	struct nvkm_device *device = clk->base.subdev.device;
	switch (nvkm_rd32(device, 0x1373f4) & 0x0000000f) {
	case 1: return read_pll(clk, 0x132020);
	case 2: return read_pll(clk, 0x132000);
	default:
		return 0;
	}
}