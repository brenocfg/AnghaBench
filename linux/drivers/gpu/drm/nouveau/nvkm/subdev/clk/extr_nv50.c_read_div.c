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
struct nvkm_device {int chipset; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nv50_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static u32
read_div(struct nv50_clk *clk)
{
	struct nvkm_device *device = clk->base.subdev.device;
	switch (device->chipset) {
	case 0x50: /* it exists, but only has bit 31, not the dividers.. */
	case 0x84:
	case 0x86:
	case 0x98:
	case 0xa0:
		return nvkm_rd32(device, 0x004700);
	case 0x92:
	case 0x94:
	case 0x96:
		return nvkm_rd32(device, 0x004800);
	default:
		return 0x00000000;
	}
}