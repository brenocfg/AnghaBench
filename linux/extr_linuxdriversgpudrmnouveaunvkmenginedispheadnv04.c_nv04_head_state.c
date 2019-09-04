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
struct nvkm_head_state {int vblanks; int vtotal; int vblanke; int hblanks; int htotal; int hblanke; } ;
struct nvkm_head {int id; TYPE_3__* disp; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;

/* Variables and functions */
 int nvkm_rd32 (struct nvkm_device*,int const) ; 

__attribute__((used)) static void
nv04_head_state(struct nvkm_head *head, struct nvkm_head_state *state)
{
	struct nvkm_device *device = head->disp->engine.subdev.device;
	const u32 hoff = head->id * 0x0200;
	state->vblanks = nvkm_rd32(device, 0x680800 + hoff) & 0x0000ffff;
	state->vtotal  = nvkm_rd32(device, 0x680804 + hoff) & 0x0000ffff;
	state->vblanke = state->vtotal - 1;
	state->hblanks = nvkm_rd32(device, 0x680820 + hoff) & 0x0000ffff;
	state->htotal  = nvkm_rd32(device, 0x680824 + hoff) & 0x0000ffff;
	state->hblanke = state->htotal - 1;
}