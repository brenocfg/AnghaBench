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
struct nvkm_head_state {int vblanke; int hblanke; int vblanks; int hblanks; int vtotal; int htotal; int vsynce; int hsynce; int hz; } ;
struct nvkm_head {int id; struct nvkm_head_state arm; TYPE_3__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int const) ; 

__attribute__((used)) static void
nv50_head_state(struct nvkm_head *head, struct nvkm_head_state *state)
{
	struct nvkm_device *device = head->disp->engine.subdev.device;
	const u32 hoff = head->id * 0x540 + (state == &head->arm) * 4;
	u32 data;

	data = nvkm_rd32(device, 0x610ae8 + hoff);
	state->vblanke = (data & 0xffff0000) >> 16;
	state->hblanke = (data & 0x0000ffff);
	data = nvkm_rd32(device, 0x610af0 + hoff);
	state->vblanks = (data & 0xffff0000) >> 16;
	state->hblanks = (data & 0x0000ffff);
	data = nvkm_rd32(device, 0x610af8 + hoff);
	state->vtotal = (data & 0xffff0000) >> 16;
	state->htotal = (data & 0x0000ffff);
	data = nvkm_rd32(device, 0x610b00 + hoff);
	state->vsynce = (data & 0xffff0000) >> 16;
	state->hsynce = (data & 0x0000ffff);
	state->hz = (nvkm_rd32(device, 0x610ad0 + hoff) & 0x003fffff) * 1000;
}