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
 int /*<<< orphan*/  nv_clk_src_mpllsrc ; 
 int /*<<< orphan*/  nv_clk_src_mpllsrcref ; 
 int nvkm_clk_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_div (struct gf100_clk*,int,int,int) ; 

__attribute__((used)) static u32
read_pll(struct gf100_clk *clk, u32 pll)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 ctrl = nvkm_rd32(device, pll + 0x00);
	u32 coef = nvkm_rd32(device, pll + 0x04);
	u32 P = (coef & 0x003f0000) >> 16;
	u32 N = (coef & 0x0000ff00) >> 8;
	u32 M = (coef & 0x000000ff) >> 0;
	u32 sclk;

	if (!(ctrl & 0x00000001))
		return 0;

	switch (pll) {
	case 0x00e800:
	case 0x00e820:
		sclk = device->crystal;
		P = 1;
		break;
	case 0x132000:
		sclk = nvkm_clk_read(&clk->base, nv_clk_src_mpllsrc);
		break;
	case 0x132020:
		sclk = nvkm_clk_read(&clk->base, nv_clk_src_mpllsrcref);
		break;
	case 0x137000:
	case 0x137020:
	case 0x137040:
	case 0x1370e0:
		sclk = read_div(clk, (pll & 0xff) / 0x20, 0x137120, 0x137140);
		break;
	default:
		return 0;
	}

	return sclk * N / M / P;
}