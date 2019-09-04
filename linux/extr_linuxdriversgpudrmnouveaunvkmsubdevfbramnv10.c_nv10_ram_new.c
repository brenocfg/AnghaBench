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
struct nvkm_ram {int dummy; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_fb {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;
typedef  enum nvkm_ram_type { ____Placeholder_nvkm_ram_type } nvkm_ram_type ;

/* Variables and functions */
 int NVKM_RAM_TYPE_DDR1 ; 
 int NVKM_RAM_TYPE_SDRAM ; 
 int /*<<< orphan*/  nv04_ram_func ; 
 int nvkm_ram_new_ (int /*<<< orphan*/ *,struct nvkm_fb*,int,int,struct nvkm_ram**) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
nv10_ram_new(struct nvkm_fb *fb, struct nvkm_ram **pram)
{
	struct nvkm_device *device = fb->subdev.device;
	u32 size = nvkm_rd32(device, 0x10020c) & 0xff000000;
	u32 cfg0 = nvkm_rd32(device, 0x100200);
	enum nvkm_ram_type type;

	if (cfg0 & 0x00000001)
		type = NVKM_RAM_TYPE_DDR1;
	else
		type = NVKM_RAM_TYPE_SDRAM;

	return nvkm_ram_new_(&nv04_ram_func, fb, type, size, pram);
}