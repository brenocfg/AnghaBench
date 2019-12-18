#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int chipset; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;
struct nv50_clk {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  nv_clk_src_crystal ; 
 int /*<<< orphan*/  nv_clk_src_href ; 
 int nvkm_clk_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static u32
read_pll_src(struct nv50_clk *clk, u32 base)
{
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;
	u32 coef, ref = nvkm_clk_read(&clk->base, nv_clk_src_crystal);
	u32 rsel = nvkm_rd32(device, 0x00e18c);
	int P, N, M, id;

	switch (device->chipset) {
	case 0x50:
	case 0xa0:
		switch (base) {
		case 0x4020:
		case 0x4028: id = !!(rsel & 0x00000004); break;
		case 0x4008: id = !!(rsel & 0x00000008); break;
		case 0x4030: id = 0; break;
		default:
			nvkm_error(subdev, "ref: bad pll %06x\n", base);
			return 0;
		}

		coef = nvkm_rd32(device, 0x00e81c + (id * 0x0c));
		ref *=  (coef & 0x01000000) ? 2 : 4;
		P    =  (coef & 0x00070000) >> 16;
		N    = ((coef & 0x0000ff00) >> 8) + 1;
		M    = ((coef & 0x000000ff) >> 0) + 1;
		break;
	case 0x84:
	case 0x86:
	case 0x92:
		coef = nvkm_rd32(device, 0x00e81c);
		P    = (coef & 0x00070000) >> 16;
		N    = (coef & 0x0000ff00) >> 8;
		M    = (coef & 0x000000ff) >> 0;
		break;
	case 0x94:
	case 0x96:
	case 0x98:
		rsel = nvkm_rd32(device, 0x00c050);
		switch (base) {
		case 0x4020: rsel = (rsel & 0x00000003) >> 0; break;
		case 0x4008: rsel = (rsel & 0x0000000c) >> 2; break;
		case 0x4028: rsel = (rsel & 0x00001800) >> 11; break;
		case 0x4030: rsel = 3; break;
		default:
			nvkm_error(subdev, "ref: bad pll %06x\n", base);
			return 0;
		}

		switch (rsel) {
		case 0: id = 1; break;
		case 1: return nvkm_clk_read(&clk->base, nv_clk_src_crystal);
		case 2: return nvkm_clk_read(&clk->base, nv_clk_src_href);
		case 3: id = 0; break;
		}

		coef =  nvkm_rd32(device, 0x00e81c + (id * 0x28));
		P    = (nvkm_rd32(device, 0x00e824 + (id * 0x28)) >> 16) & 7;
		P   += (coef & 0x00070000) >> 16;
		N    = (coef & 0x0000ff00) >> 8;
		M    = (coef & 0x000000ff) >> 0;
		break;
	default:
		BUG();
	}

	if (M)
		return (ref * N / M) >> P;

	return 0;
}