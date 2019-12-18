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
struct nvkm_device {struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nv50_devinit {TYPE_2__ base; } ;

/* Variables and functions */
 int nvbios_rd32 (struct nvkm_bios*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
pmu_code(struct nv50_devinit *init, u32 pmu, u32 img, u32 len, bool sec)
{
	struct nvkm_device *device = init->base.subdev.device;
	struct nvkm_bios *bios = device->bios;
	int i;

	nvkm_wr32(device, 0x10a180, 0x01000000 | (sec ? 0x10000000 : 0) | pmu);
	for (i = 0; i < len; i += 4) {
		if ((i & 0xff) == 0)
			nvkm_wr32(device, 0x10a188, (pmu + i) >> 8);
		nvkm_wr32(device, 0x10a184, nvbios_rd32(bios, img + i));
	}

	while (i & 0xff) {
		nvkm_wr32(device, 0x10a184, 0x00000000);
		i += 4;
	}
}