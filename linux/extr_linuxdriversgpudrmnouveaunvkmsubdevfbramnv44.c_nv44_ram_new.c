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
 int NVKM_RAM_TYPE_DDR2 ; 
 int NVKM_RAM_TYPE_GDDR3 ; 
 int NVKM_RAM_TYPE_UNKNOWN ; 
 int nv40_ram_new_ (struct nvkm_fb*,int,int,struct nvkm_ram**) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

int
nv44_ram_new(struct nvkm_fb *fb, struct nvkm_ram **pram)
{
	struct nvkm_device *device = fb->subdev.device;
	u32  size = nvkm_rd32(device, 0x10020c) & 0xff000000;
	u32 fb474 = nvkm_rd32(device, 0x100474);
	enum nvkm_ram_type type = NVKM_RAM_TYPE_UNKNOWN;

	if (fb474 & 0x00000004)
		type = NVKM_RAM_TYPE_GDDR3;
	if (fb474 & 0x00000002)
		type = NVKM_RAM_TYPE_DDR2;
	if (fb474 & 0x00000001)
		type = NVKM_RAM_TYPE_DDR1;

	return nv40_ram_new_(fb, type, size, pram);
}