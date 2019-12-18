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
struct nvkm_fifo {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct TYPE_4__ {TYPE_1__ engine; } ;
struct gf100_fifo {TYPE_2__ base; } ;

/* Variables and functions */
 int __ffs (int) ; 
 struct gf100_fifo* gf100_fifo (struct nvkm_fifo*) ; 
 int /*<<< orphan*/  gf100_fifo_intr_engine (struct gf100_fifo*) ; 
 int /*<<< orphan*/  gf100_fifo_intr_fault (TYPE_2__*,int) ; 
 int /*<<< orphan*/  gf100_fifo_intr_pbdma (struct gf100_fifo*,int) ; 
 int /*<<< orphan*/  gf100_fifo_intr_runlist (struct gf100_fifo*) ; 
 int /*<<< orphan*/  gf100_fifo_intr_sched (struct gf100_fifo*) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_warn (struct nvkm_subdev*,char*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_fifo_intr(struct nvkm_fifo *base)
{
	struct gf100_fifo *fifo = gf100_fifo(base);
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 mask = nvkm_rd32(device, 0x002140);
	u32 stat = nvkm_rd32(device, 0x002100) & mask;

	if (stat & 0x00000001) {
		u32 intr = nvkm_rd32(device, 0x00252c);
		nvkm_warn(subdev, "INTR 00000001: %08x\n", intr);
		nvkm_wr32(device, 0x002100, 0x00000001);
		stat &= ~0x00000001;
	}

	if (stat & 0x00000100) {
		gf100_fifo_intr_sched(fifo);
		nvkm_wr32(device, 0x002100, 0x00000100);
		stat &= ~0x00000100;
	}

	if (stat & 0x00010000) {
		u32 intr = nvkm_rd32(device, 0x00256c);
		nvkm_warn(subdev, "INTR 00010000: %08x\n", intr);
		nvkm_wr32(device, 0x002100, 0x00010000);
		stat &= ~0x00010000;
	}

	if (stat & 0x01000000) {
		u32 intr = nvkm_rd32(device, 0x00258c);
		nvkm_warn(subdev, "INTR 01000000: %08x\n", intr);
		nvkm_wr32(device, 0x002100, 0x01000000);
		stat &= ~0x01000000;
	}

	if (stat & 0x10000000) {
		u32 mask = nvkm_rd32(device, 0x00259c);
		while (mask) {
			u32 unit = __ffs(mask);
			gf100_fifo_intr_fault(&fifo->base, unit);
			nvkm_wr32(device, 0x00259c, (1 << unit));
			mask &= ~(1 << unit);
		}
		stat &= ~0x10000000;
	}

	if (stat & 0x20000000) {
		u32 mask = nvkm_rd32(device, 0x0025a0);
		while (mask) {
			u32 unit = __ffs(mask);
			gf100_fifo_intr_pbdma(fifo, unit);
			nvkm_wr32(device, 0x0025a0, (1 << unit));
			mask &= ~(1 << unit);
		}
		stat &= ~0x20000000;
	}

	if (stat & 0x40000000) {
		gf100_fifo_intr_runlist(fifo);
		stat &= ~0x40000000;
	}

	if (stat & 0x80000000) {
		gf100_fifo_intr_engine(fifo);
		stat &= ~0x80000000;
	}

	if (stat) {
		nvkm_error(subdev, "INTR %08x\n", stat);
		nvkm_mask(device, 0x002140, stat, 0x00000000);
		nvkm_wr32(device, 0x002100, stat);
	}
}