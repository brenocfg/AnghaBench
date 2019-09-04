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
struct nvkm_device {int crystal; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct gt215_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_pll (struct gt215_clk*,int,int) ; 

__attribute__((used)) static u32
read_vco(struct gt215_clk *clk, int idx)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 sctl = nvkm_rd32(device, 0x4120 + (idx * 4));

	switch (sctl & 0x00000030) {
	case 0x00000000:
		return device->crystal;
	case 0x00000020:
		return read_pll(clk, 0x41, 0x00e820);
	case 0x00000030:
		return read_pll(clk, 0x42, 0x00e8a0);
	default:
		return 0;
	}
}