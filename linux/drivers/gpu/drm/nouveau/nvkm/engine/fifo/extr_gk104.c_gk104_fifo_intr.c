#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_5__ {struct nvkm_subdev subdev; } ;
struct TYPE_8__ {TYPE_1__ engine; } ;
struct gk104_fifo {TYPE_4__ base; TYPE_3__* func; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fault ) (TYPE_4__*,int) ;} ;
struct TYPE_7__ {TYPE_2__ intr; } ;

/* Variables and functions */
 int __ffs (int) ; 
 struct gk104_fifo* gk104_fifo (struct nvkm_fifo*) ; 
 int /*<<< orphan*/  gk104_fifo_intr_bind (struct gk104_fifo*) ; 
 int /*<<< orphan*/  gk104_fifo_intr_chsw (struct gk104_fifo*) ; 
 int /*<<< orphan*/  gk104_fifo_intr_dropped_fault (struct gk104_fifo*) ; 
 int /*<<< orphan*/  gk104_fifo_intr_engine (struct gk104_fifo*) ; 
 int /*<<< orphan*/  gk104_fifo_intr_pbdma_0 (struct gk104_fifo*,int) ; 
 int /*<<< orphan*/  gk104_fifo_intr_pbdma_1 (struct gk104_fifo*,int) ; 
 int /*<<< orphan*/  gk104_fifo_intr_runlist (struct gk104_fifo*) ; 
 int /*<<< orphan*/  gk104_fifo_intr_sched (struct gk104_fifo*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,...) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int) ; 

__attribute__((used)) static void
gk104_fifo_intr(struct nvkm_fifo *base)
{
	struct gk104_fifo *fifo = gk104_fifo(base);
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 mask = nvkm_rd32(device, 0x002140);
	u32 stat = nvkm_rd32(device, 0x002100) & mask;

	if (stat & 0x00000001) {
		gk104_fifo_intr_bind(fifo);
		nvkm_wr32(device, 0x002100, 0x00000001);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000010) {
		nvkm_error(subdev, "PIO_ERROR\n");
		nvkm_wr32(device, 0x002100, 0x00000010);
		stat &= ~0x00000010;
	}

	if (stat & 0x00000100) {
		gk104_fifo_intr_sched(fifo);
		nvkm_wr32(device, 0x002100, 0x00000100);
		stat &= ~0x00000100;
	}

	if (stat & 0x00010000) {
		gk104_fifo_intr_chsw(fifo);
		nvkm_wr32(device, 0x002100, 0x00010000);
		stat &= ~0x00010000;
	}

	if (stat & 0x00800000) {
		nvkm_error(subdev, "FB_FLUSH_TIMEOUT\n");
		nvkm_wr32(device, 0x002100, 0x00800000);
		stat &= ~0x00800000;
	}

	if (stat & 0x01000000) {
		nvkm_error(subdev, "LB_ERROR\n");
		nvkm_wr32(device, 0x002100, 0x01000000);
		stat &= ~0x01000000;
	}

	if (stat & 0x08000000) {
		gk104_fifo_intr_dropped_fault(fifo);
		nvkm_wr32(device, 0x002100, 0x08000000);
		stat &= ~0x08000000;
	}

	if (stat & 0x10000000) {
		u32 mask = nvkm_rd32(device, 0x00259c);
		while (mask) {
			u32 unit = __ffs(mask);
			fifo->func->intr.fault(&fifo->base, unit);
			nvkm_wr32(device, 0x00259c, (1 << unit));
			mask &= ~(1 << unit);
		}
		stat &= ~0x10000000;
	}

	if (stat & 0x20000000) {
		u32 mask = nvkm_rd32(device, 0x0025a0);
		while (mask) {
			u32 unit = __ffs(mask);
			gk104_fifo_intr_pbdma_0(fifo, unit);
			gk104_fifo_intr_pbdma_1(fifo, unit);
			nvkm_wr32(device, 0x0025a0, (1 << unit));
			mask &= ~(1 << unit);
		}
		stat &= ~0x20000000;
	}

	if (stat & 0x40000000) {
		gk104_fifo_intr_runlist(fifo);
		stat &= ~0x40000000;
	}

	if (stat & 0x80000000) {
		nvkm_wr32(device, 0x002100, 0x80000000);
		gk104_fifo_intr_engine(fifo);
		stat &= ~0x80000000;
	}

	if (stat) {
		nvkm_error(subdev, "INTR %08x\n", stat);
		nvkm_mask(device, 0x002140, stat, 0x00000000);
		nvkm_wr32(device, 0x002100, stat);
	}
}