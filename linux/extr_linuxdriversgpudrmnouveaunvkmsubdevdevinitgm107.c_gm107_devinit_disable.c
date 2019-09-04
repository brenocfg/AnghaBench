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
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_devinit {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 unsigned long long NVKM_ENGINE_CE0 ; 
 unsigned long long NVKM_ENGINE_CE2 ; 
 unsigned long long NVKM_ENGINE_DISP ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

u64
gm107_devinit_disable(struct nvkm_devinit *init)
{
	struct nvkm_device *device = init->subdev.device;
	u32 r021c00 = nvkm_rd32(device, 0x021c00);
	u32 r021c04 = nvkm_rd32(device, 0x021c04);
	u64 disable = 0ULL;

	if (r021c00 & 0x00000001)
		disable |= (1ULL << NVKM_ENGINE_CE0);
	if (r021c00 & 0x00000004)
		disable |= (1ULL << NVKM_ENGINE_CE2);
	if (r021c04 & 0x00000001)
		disable |= (1ULL << NVKM_ENGINE_DISP);

	return disable;
}