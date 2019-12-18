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
struct gt215_clk {TYPE_2__ base; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_clk (struct gt215_clk*,int,int) ; 

__attribute__((used)) static u32
read_pll(struct gt215_clk *clk, int idx, u32 pll)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 ctrl = nvkm_rd32(device, pll + 0);
	u32 sclk = 0, P = 1, N = 1, M = 1;
	u32 MP;

	if (!(ctrl & 0x00000008)) {
		if (ctrl & 0x00000001) {
			u32 coef = nvkm_rd32(device, pll + 4);
			M = (coef & 0x000000ff) >> 0;
			N = (coef & 0x0000ff00) >> 8;
			P = (coef & 0x003f0000) >> 16;

			/* no post-divider on these..
			 * XXX: it looks more like two post-"dividers" that
			 * cross each other out in the default RPLL config */
			if ((pll & 0x00ff00) == 0x00e800)
				P = 1;

			sclk = read_clk(clk, 0x00 + idx, false);
		}
	} else {
		sclk = read_clk(clk, 0x10 + idx, false);
	}

	MP = M * P;

	if (!MP)
		return 0;

	return sclk * N / MP;
}