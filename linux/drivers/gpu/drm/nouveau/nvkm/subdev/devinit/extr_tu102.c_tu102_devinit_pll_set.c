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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_devinit {struct nvkm_subdev subdev; } ;
struct nvkm_device {int /*<<< orphan*/  bios; } ;
struct nvbios_pll {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PLL_VPLL0 131 
#define  PLL_VPLL1 130 
#define  PLL_VPLL2 129 
#define  PLL_VPLL3 128 
 int gt215_pll_calc (struct nvkm_subdev*,struct nvbios_pll*,int,int*,int*,int*,int*) ; 
 int nvbios_pll_parse (int /*<<< orphan*/ ,int,struct nvbios_pll*) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static int
tu102_devinit_pll_set(struct nvkm_devinit *init, u32 type, u32 freq)
{
	struct nvkm_subdev *subdev = &init->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvbios_pll info;
	int head = type - PLL_VPLL0;
	int N, fN, M, P;
	int ret;

	ret = nvbios_pll_parse(device->bios, type, &info);
	if (ret)
		return ret;

	ret = gt215_pll_calc(subdev, &info, freq, &N, &fN, &M, &P);
	if (ret < 0)
		return ret;

	switch (info.type) {
	case PLL_VPLL0:
	case PLL_VPLL1:
	case PLL_VPLL2:
	case PLL_VPLL3:
		nvkm_wr32(device, 0x00ef10 + (head * 0x40), fN << 16);
		nvkm_wr32(device, 0x00ef04 + (head * 0x40), (P << 16) |
							    (N <<  8) |
							    (M <<  0));
		/*XXX*/
		nvkm_wr32(device, 0x00ef0c + (head * 0x40), 0x00000900);
		nvkm_wr32(device, 0x00ef00 + (head * 0x40), 0x02000014);
		break;
	default:
		nvkm_warn(subdev, "%08x/%dKhz unimplemented\n", type, freq);
		ret = -EINVAL;
		break;
	}

	return ret;
}