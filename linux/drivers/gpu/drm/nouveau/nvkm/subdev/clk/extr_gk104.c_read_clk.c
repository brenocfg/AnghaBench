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
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct gk104_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_div (struct gk104_clk*,int,int,int) ; 
 int read_pll (struct gk104_clk*,int) ; 

__attribute__((used)) static u32
read_clk(struct gk104_clk *clk, int idx)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 sctl = nvkm_rd32(device, 0x137250 + (idx * 4));
	u32 sclk, sdiv;

	if (idx < 7) {
		u32 ssel = nvkm_rd32(device, 0x137100);
		if (ssel & (1 << idx)) {
			sclk = read_pll(clk, 0x137000 + (idx * 0x20));
			sdiv = 1;
		} else {
			sclk = read_div(clk, idx, 0x137160, 0x1371d0);
			sdiv = 0;
		}
	} else {
		u32 ssrc = nvkm_rd32(device, 0x137160 + (idx * 0x04));
		if ((ssrc & 0x00000003) == 0x00000003) {
			sclk = read_div(clk, idx, 0x137160, 0x1371d0);
			if (ssrc & 0x00000100) {
				if (ssrc & 0x40000000)
					sclk = read_pll(clk, 0x1370e0);
				sdiv = 1;
			} else {
				sdiv = 0;
			}
		} else {
			sclk = read_div(clk, idx, 0x137160, 0x1371d0);
			sdiv = 0;
		}
	}

	if (sctl & 0x80000000) {
		if (sdiv)
			sdiv = ((sctl & 0x00003f00) >> 8) + 2;
		else
			sdiv = ((sctl & 0x0000003f) >> 0) + 2;
		return (sclk * 2) / sdiv;
	}

	return sclk;
}