#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_fault_data {int addr; int inst; int engine; int valid; int gpc; int hub; int access; int client; int reason; scalar_t__ time; } ;
struct nvkm_fault {struct nvkm_subdev subdev; } ;
struct nvkm_device {int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_fifo_fault (int /*<<< orphan*/ ,struct nvkm_fault_data*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 

__attribute__((used)) static void
tu102_fault_intr_fault(struct nvkm_fault *fault)
{
	struct nvkm_subdev *subdev = &fault->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_fault_data info;
	const u32 addrlo = nvkm_rd32(device, 0xb83080);
	const u32 addrhi = nvkm_rd32(device, 0xb83084);
	const u32  info0 = nvkm_rd32(device, 0xb83088);
	const u32 insthi = nvkm_rd32(device, 0xb8308c);
	const u32  info1 = nvkm_rd32(device, 0xb83090);

	info.addr = ((u64)addrhi << 32) | addrlo;
	info.inst = ((u64)insthi << 32) | (info0 & 0xfffff000);
	info.time = 0;
	info.engine = (info0 & 0x000000ff);
	info.valid  = (info1 & 0x80000000) >> 31;
	info.gpc    = (info1 & 0x1f000000) >> 24;
	info.hub    = (info1 & 0x00100000) >> 20;
	info.access = (info1 & 0x000f0000) >> 16;
	info.client = (info1 & 0x00007f00) >> 8;
	info.reason = (info1 & 0x0000001f);

	nvkm_fifo_fault(device->fifo, &info);
}