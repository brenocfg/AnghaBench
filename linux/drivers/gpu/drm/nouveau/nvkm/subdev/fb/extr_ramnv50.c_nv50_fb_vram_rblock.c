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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_ram {int parts; int size; TYPE_1__* fb; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_2__ {struct nvkm_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,...) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int) ; 

__attribute__((used)) static u32
nv50_fb_vram_rblock(struct nvkm_ram *ram)
{
	struct nvkm_subdev *subdev = &ram->fb->subdev;
	struct nvkm_device *device = subdev->device;
	int colbits, rowbitsa, rowbitsb, banks;
	u64 rowsize, predicted;
	u32 r0, r4, rt, rblock_size;

	r0 = nvkm_rd32(device, 0x100200);
	r4 = nvkm_rd32(device, 0x100204);
	rt = nvkm_rd32(device, 0x100250);
	nvkm_debug(subdev, "memcfg %08x %08x %08x %08x\n",
		   r0, r4, rt, nvkm_rd32(device, 0x001540));

	colbits  =  (r4 & 0x0000f000) >> 12;
	rowbitsa = ((r4 & 0x000f0000) >> 16) + 8;
	rowbitsb = ((r4 & 0x00f00000) >> 20) + 8;
	banks    = 1 << (((r4 & 0x03000000) >> 24) + 2);

	rowsize = ram->parts * banks * (1 << colbits) * 8;
	predicted = rowsize << rowbitsa;
	if (r0 & 0x00000004)
		predicted += rowsize << rowbitsb;

	if (predicted != ram->size) {
		nvkm_warn(subdev, "memory controller reports %d MiB VRAM\n",
			  (u32)(ram->size >> 20));
	}

	rblock_size = rowsize;
	if (rt & 1)
		rblock_size *= 3;

	nvkm_debug(subdev, "rblock %d bytes\n", rblock_size);
	return rblock_size;
}