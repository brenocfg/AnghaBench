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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_fault {int /*<<< orphan*/  event; scalar_t__* buffer; struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gv100_fault_intr_fault (struct nvkm_fault*) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int) ; 
 int /*<<< orphan*/  nvkm_event_send (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gv100_fault_intr(struct nvkm_fault *fault)
{
	struct nvkm_subdev *subdev = &fault->subdev;
	struct nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x100a20);

	if (stat & 0x80000000) {
		gv100_fault_intr_fault(fault);
		nvkm_wr32(device, 0x100e60, 0x80000000);
		stat &= ~0x80000000;
	}

	if (stat & 0x20000000) {
		if (fault->buffer[0]) {
			nvkm_event_send(&fault->event, 1, 0, NULL, 0);
			stat &= ~0x20000000;
		}
	}

	if (stat & 0x08000000) {
		if (fault->buffer[1]) {
			nvkm_event_send(&fault->event, 1, 1, NULL, 0);
			stat &= ~0x08000000;
		}
	}

	if (stat) {
		nvkm_debug(subdev, "intr %08x\n", stat);
	}
}