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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_fault_data {int inst; int addr; int engine; int valid; int gpc; int client; int access; int hub; int reason; scalar_t__ time; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gk104_fifo {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_fifo_fault (TYPE_2__*,struct nvkm_fault_data*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static void
gk104_fifo_intr_fault(struct gk104_fifo *fifo, int unit)
{
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 inst = nvkm_rd32(device, 0x002800 + (unit * 0x10));
	u32 valo = nvkm_rd32(device, 0x002804 + (unit * 0x10));
	u32 vahi = nvkm_rd32(device, 0x002808 + (unit * 0x10));
	u32 type = nvkm_rd32(device, 0x00280c + (unit * 0x10));
	struct nvkm_fault_data info;

	info.inst   =  (u64)inst << 12;
	info.addr   = ((u64)vahi << 32) | valo;
	info.time   = 0;
	info.engine = unit;
	info.valid  = 1;
	info.gpc    = (type & 0x1f000000) >> 24;
	info.client = (type & 0x00001f00) >> 8;
	info.access = (type & 0x00000080) >> 7;
	info.hub    = (type & 0x00000040) >> 6;
	info.reason = (type & 0x000000ff);

	nvkm_fifo_fault(&fifo->base, &info);
}