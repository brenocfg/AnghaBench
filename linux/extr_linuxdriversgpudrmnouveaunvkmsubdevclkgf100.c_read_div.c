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
struct gf100_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_vco (struct gf100_clk*,int) ; 

__attribute__((used)) static u32
read_div(struct gf100_clk *clk, int doff, u32 dsrc, u32 dctl)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 ssrc = nvkm_rd32(device, dsrc + (doff * 4));
	u32 sclk, sctl, sdiv = 2;

	switch (ssrc & 0x00000003) {
	case 0:
		if ((ssrc & 0x00030000) != 0x00030000)
			return device->crystal;
		return 108000;
	case 2:
		return 100000;
	case 3:
		sclk = read_vco(clk, dsrc + (doff * 4));

		/* Memclk has doff of 0 despite its alt. location */
		if (doff <= 2) {
			sctl = nvkm_rd32(device, dctl + (doff * 4));

			if (sctl & 0x80000000) {
				if (ssrc & 0x100)
					sctl >>= 8;

				sdiv = (sctl & 0x3f) + 2;
			}
		}

		return (sclk * 2) / sdiv;
	default:
		return 0;
	}
}