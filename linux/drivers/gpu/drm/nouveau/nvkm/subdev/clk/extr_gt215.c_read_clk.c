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
struct nvkm_device {int chipset; int crystal; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_3__ {TYPE_2__ subdev; } ;
struct gt215_clk {TYPE_1__ base; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_vco (struct gt215_clk*,int) ; 

__attribute__((used)) static u32
read_clk(struct gt215_clk *clk, int idx, bool ignore_en)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 sctl, sdiv, sclk;

	/* refclk for the 0xe8xx plls is a fixed frequency */
	if (idx >= 0x40) {
		if (device->chipset == 0xaf) {
			/* no joke.. seriously.. sigh.. */
			return nvkm_rd32(device, 0x00471c) * 1000;
		}

		return device->crystal;
	}

	sctl = nvkm_rd32(device, 0x4120 + (idx * 4));
	if (!ignore_en && !(sctl & 0x00000100))
		return 0;

	/* out_alt */
	if (sctl & 0x00000400)
		return 108000;

	/* vco_out */
	switch (sctl & 0x00003000) {
	case 0x00000000:
		if (!(sctl & 0x00000200))
			return device->crystal;
		return 0;
	case 0x00002000:
		if (sctl & 0x00000040)
			return 108000;
		return 100000;
	case 0x00003000:
		/* vco_enable */
		if (!(sctl & 0x00000001))
			return 0;

		sclk = read_vco(clk, idx);
		sdiv = ((sctl & 0x003f0000) >> 16) + 2;
		return (sclk * 2) / sdiv;
	default:
		return 0;
	}
}