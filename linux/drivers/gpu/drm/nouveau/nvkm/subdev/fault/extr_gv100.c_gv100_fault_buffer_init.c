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
struct nvkm_fault_buffer {int id; int /*<<< orphan*/  addr; TYPE_2__* fault; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int const,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gv100_fault_buffer_init(struct nvkm_fault_buffer *buffer)
{
	struct nvkm_device *device = buffer->fault->subdev.device;
	const u32 foff = buffer->id * 0x14;

	nvkm_mask(device, 0x100e34 + foff, 0xc0000000, 0x40000000);
	nvkm_wr32(device, 0x100e28 + foff, upper_32_bits(buffer->addr));
	nvkm_wr32(device, 0x100e24 + foff, lower_32_bits(buffer->addr));
	nvkm_mask(device, 0x100e34 + foff, 0x80000000, 0x80000000);
}