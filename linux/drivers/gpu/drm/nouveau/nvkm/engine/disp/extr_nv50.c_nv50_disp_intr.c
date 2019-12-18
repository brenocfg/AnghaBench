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
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv50_disp {int super; int /*<<< orphan*/  supervisor; int /*<<< orphan*/  wq; TYPE_3__ base; } ;

/* Variables and functions */
 int __ffs (int) ; 
 int /*<<< orphan*/  nv50_disp_chan_uevent_send (struct nv50_disp*,int) ; 
 int /*<<< orphan*/  nv50_disp_intr_error (struct nv50_disp*,int) ; 
 int /*<<< orphan*/  nvkm_disp_vblank (TYPE_3__*,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nv50_disp_intr(struct nv50_disp *disp)
{
	struct nvkm_device *device = disp->base.engine.subdev.device;
	u32 intr0 = nvkm_rd32(device, 0x610020);
	u32 intr1 = nvkm_rd32(device, 0x610024);

	while (intr0 & 0x001f0000) {
		u32 chid = __ffs(intr0 & 0x001f0000) - 16;
		nv50_disp_intr_error(disp, chid);
		intr0 &= ~(0x00010000 << chid);
	}

	while (intr0 & 0x0000001f) {
		u32 chid = __ffs(intr0 & 0x0000001f);
		nv50_disp_chan_uevent_send(disp, chid);
		intr0 &= ~(0x00000001 << chid);
	}

	if (intr1 & 0x00000004) {
		nvkm_disp_vblank(&disp->base, 0);
		nvkm_wr32(device, 0x610024, 0x00000004);
	}

	if (intr1 & 0x00000008) {
		nvkm_disp_vblank(&disp->base, 1);
		nvkm_wr32(device, 0x610024, 0x00000008);
	}

	if (intr1 & 0x00000070) {
		disp->super = (intr1 & 0x00000070);
		queue_work(disp->wq, &disp->supervisor);
		nvkm_wr32(device, 0x610024, disp->super);
	}
}