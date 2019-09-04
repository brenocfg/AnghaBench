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
 int /*<<< orphan*/  nv_clk_src_dom6 ; 
 int nvkm_clk_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int read_pll_ref (struct nv50_clk*,int) ; 

__attribute__((used)) static u32
read_pll(struct nv50_clk *clk, u32 base)
{
	struct nvkm_device *device = clk->base.subdev.device;
	u32 mast = nvkm_rd32(device, 0x00c040);
	u32 ctrl = nvkm_rd32(device, base + 0);
	u32 coef = nvkm_rd32(device, base + 4);
	u32 ref = read_pll_ref(clk, base);
	u32 freq = 0;
	int N1, N2, M1, M2;

	if (base == 0x004028 && (mast & 0x00100000)) {
		/* wtf, appears to only disable post-divider on gt200 */
		if (device->chipset != 0xa0)
			return nvkm_clk_read(&clk->base, nv_clk_src_dom6);
	}

	N2 = (coef & 0xff000000) >> 24;
	M2 = (coef & 0x00ff0000) >> 16;
	N1 = (coef & 0x0000ff00) >> 8;
	M1 = (coef & 0x000000ff);
	if ((ctrl & 0x80000000) && M1) {
		freq = ref * N1 / M1;
		if ((ctrl & 0x40000100) == 0x40000000) {
			if (M2)
				freq = freq * N2 / M2;
			else
				freq = 0;
		}
	}

	return freq;
}