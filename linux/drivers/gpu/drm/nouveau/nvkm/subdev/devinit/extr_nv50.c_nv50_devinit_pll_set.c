#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_devinit {struct nvkm_subdev subdev; } ;
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_pll {int type; int bias_p; scalar_t__ reg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PLL_MEMORY 130 
#define  PLL_VPLL0 129 
#define  PLL_VPLL1 128 
 int nv04_pll_calc (struct nvkm_subdev*,struct nvbios_pll*,int /*<<< orphan*/ ,int*,int*,int*,int*,int*) ; 
 int nvbios_pll_parse (struct nvkm_bios*,int /*<<< orphan*/ ,struct nvbios_pll*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,...) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,scalar_t__,int) ; 

int
nv50_devinit_pll_set(struct nvkm_devinit *init, u32 type, u32 freq)
{
	struct nvkm_subdev *subdev = &init->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_bios *bios = device->bios;
	struct nvbios_pll info;
	int N1, M1, N2, M2, P;
	int ret;

	ret = nvbios_pll_parse(bios, type, &info);
	if (ret) {
		nvkm_error(subdev, "failed to retrieve pll data, %d\n", ret);
		return ret;
	}

	ret = nv04_pll_calc(subdev, &info, freq, &N1, &M1, &N2, &M2, &P);
	if (!ret) {
		nvkm_error(subdev, "failed pll calculation\n");
		return -EINVAL;
	}

	switch (info.type) {
	case PLL_VPLL0:
	case PLL_VPLL1:
		nvkm_wr32(device, info.reg + 0, 0x10000611);
		nvkm_mask(device, info.reg + 4, 0x00ff00ff, (M1 << 16) | N1);
		nvkm_mask(device, info.reg + 8, 0x7fff00ff, (P  << 28) |
							    (M2 << 16) | N2);
		break;
	case PLL_MEMORY:
		nvkm_mask(device, info.reg + 0, 0x01ff0000,
					        (P << 22) |
						(info.bias_p << 19) |
						(P << 16));
		nvkm_wr32(device, info.reg + 4, (N1 << 8) | M1);
		break;
	default:
		nvkm_mask(device, info.reg + 0, 0x00070000, (P << 16));
		nvkm_wr32(device, info.reg + 4, (N1 << 8) | M1);
		break;
	}

	return 0;
}