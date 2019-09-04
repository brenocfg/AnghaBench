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
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct nv50_disp {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_disp_vblank (TYPE_2__*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gv100_disp_intr_head_timing(struct nv50_disp *disp, int head)
{
	struct nvkm_subdev *subdev = &disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x611800 + (head * 0x04));

	/* LAST_DATA, LOADV. */
	if (stat & 0x00000003) {
		nvkm_wr32(device, 0x611800 + (head * 0x04), stat & 0x00000003);
		stat &= ~0x00000003;
	}

	if (stat & 0x00000004) {
		nvkm_disp_vblank(&disp->base, head);
		nvkm_wr32(device, 0x611800 + (head * 0x04), 0x00000004);
		stat &= ~0x00000004;
	}

	if (stat) {
		nvkm_warn(subdev, "head %08x\n", stat);
		nvkm_wr32(device, 0x611800 + (head * 0x04), stat);
	}
}