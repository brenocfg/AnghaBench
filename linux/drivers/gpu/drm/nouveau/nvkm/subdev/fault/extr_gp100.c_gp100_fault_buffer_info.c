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
struct nvkm_fault_buffer {int get; int put; TYPE_2__* fault; int /*<<< orphan*/  entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_rd32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gp100_fault_buffer_info(struct nvkm_fault_buffer *buffer)
{
	buffer->entries = nvkm_rd32(buffer->fault->subdev.device, 0x002a78);
	buffer->get = 0x002a7c;
	buffer->put = 0x002a80;
}