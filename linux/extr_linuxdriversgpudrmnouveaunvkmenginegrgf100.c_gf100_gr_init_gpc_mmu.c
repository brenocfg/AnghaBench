#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_fb {int /*<<< orphan*/  mmu_rd; int /*<<< orphan*/  mmu_wr; } ;
struct nvkm_device {struct nvkm_fb* fb; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct gf100_gr {TYPE_3__ base; } ;

/* Variables and functions */
 int nvkm_memory_addr (int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

void
gf100_gr_init_gpc_mmu(struct gf100_gr *gr)
{
	struct nvkm_device *device = gr->base.engine.subdev.device;
	struct nvkm_fb *fb = device->fb;

	nvkm_wr32(device, 0x418880, nvkm_rd32(device, 0x100c80) & 0x00000001);
	nvkm_wr32(device, 0x4188a4, 0x03000000);
	nvkm_wr32(device, 0x418888, 0x00000000);
	nvkm_wr32(device, 0x41888c, 0x00000000);
	nvkm_wr32(device, 0x418890, 0x00000000);
	nvkm_wr32(device, 0x418894, 0x00000000);
	nvkm_wr32(device, 0x4188b4, nvkm_memory_addr(fb->mmu_wr) >> 8);
	nvkm_wr32(device, 0x4188b8, nvkm_memory_addr(fb->mmu_rd) >> 8);
}