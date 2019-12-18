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
 unsigned long long NVKM_ENGINE_BSP ; 
 unsigned long long NVKM_ENGINE_CIPHER ; 
 unsigned long long NVKM_ENGINE_DISP ; 
 unsigned long long NVKM_ENGINE_MPEG ; 
 unsigned long long NVKM_ENGINE_VP ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static u64
g84_devinit_disable(struct nvkm_devinit *init)
{
	struct nvkm_device *device = init->subdev.device;
	u32 r001540 = nvkm_rd32(device, 0x001540);
	u32 r00154c = nvkm_rd32(device, 0x00154c);
	u64 disable = 0ULL;

	if (!(r001540 & 0x40000000)) {
		disable |= (1ULL << NVKM_ENGINE_MPEG);
		disable |= (1ULL << NVKM_ENGINE_VP);
		disable |= (1ULL << NVKM_ENGINE_BSP);
		disable |= (1ULL << NVKM_ENGINE_CIPHER);
	}

	if (!(r00154c & 0x00000004))
		disable |= (1ULL << NVKM_ENGINE_DISP);
	if (!(r00154c & 0x00000020))
		disable |= (1ULL << NVKM_ENGINE_BSP);
	if (!(r00154c & 0x00000040))
		disable |= (1ULL << NVKM_ENGINE_CIPHER);

	return disable;
}