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
struct nvkm_fault_buffer {TYPE_2__* fault; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_SUBDEV_FAULT ; 
 int /*<<< orphan*/  nvkm_mc_intr_mask (struct nvkm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gp100_fault_buffer_intr(struct nvkm_fault_buffer *buffer, bool enable)
{
	struct nvkm_device *device = buffer->fault->subdev.device;
	nvkm_mc_intr_mask(device, NVKM_SUBDEV_FAULT, enable);
}