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
struct nvkm_ram {int parts; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_fb {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;
typedef  enum nvkm_ram_type { ____Placeholder_nvkm_ram_type } nvkm_ram_type ;

/* Variables and functions */
 int NVKM_RAM_TYPE_DDR1 ; 
 int NVKM_RAM_TYPE_GDDR2 ; 
 int NVKM_RAM_TYPE_GDDR3 ; 
 int NVKM_RAM_TYPE_SDRAM ; 
 int NVKM_RAM_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  nv04_ram_func ; 
 int nvkm_ram_new_ (int /*<<< orphan*/ *,struct nvkm_fb*,int,int,struct nvkm_ram**) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
nv20_ram_new(struct nvkm_fb *fb, struct nvkm_ram **pram)
{
	struct nvkm_device *device = fb->subdev.device;
	u32 pbus1218 =  nvkm_rd32(device, 0x001218);
	u32     size = (nvkm_rd32(device, 0x10020c) & 0xff000000);
	enum nvkm_ram_type type = NVKM_RAM_TYPE_UNKNOWN;
	int ret;

	switch (pbus1218 & 0x00000300) {
	case 0x00000000: type = NVKM_RAM_TYPE_SDRAM; break;
	case 0x00000100: type = NVKM_RAM_TYPE_DDR1 ; break;
	case 0x00000200: type = NVKM_RAM_TYPE_GDDR3; break;
	case 0x00000300: type = NVKM_RAM_TYPE_GDDR2; break;
	}

	ret = nvkm_ram_new_(&nv04_ram_func, fb, type, size, pram);
	if (ret)
		return ret;

	(*pram)->parts = (nvkm_rd32(device, 0x100200) & 0x00000003) + 1;
	return 0;
}