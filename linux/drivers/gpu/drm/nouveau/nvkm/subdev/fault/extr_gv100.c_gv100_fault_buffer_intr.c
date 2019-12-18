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
struct nvkm_fault_buffer {scalar_t__ id; TYPE_2__* fault; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int const,int const) ; 

__attribute__((used)) static void
gv100_fault_buffer_intr(struct nvkm_fault_buffer *buffer, bool enable)
{
	struct nvkm_device *device = buffer->fault->subdev.device;
	const u32 intr = buffer->id ? 0x08000000 : 0x20000000;
	if (enable)
		nvkm_mask(device, 0x100a2c, intr, intr);
	else
		nvkm_mask(device, 0x100a34, intr, intr);
}