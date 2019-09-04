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
struct nvkm_vmm {int dummy; } ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_fault_buffer {int id; int entries; int /*<<< orphan*/  vma; int /*<<< orphan*/  mem; struct nvkm_fault* fault; } ;
struct nvkm_fault {TYPE_2__* func; struct nvkm_fault_buffer** buffer; struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_3__ {int (* entries ) (struct nvkm_fault_buffer*) ;int entry_size; } ;
struct TYPE_4__ {TYPE_1__ buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 struct nvkm_fault_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nvkm_vmm* nvkm_bar_bar2_vmm (struct nvkm_device*) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,int) ; 
 int nvkm_memory_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvkm_vmm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvkm_memory_new (struct nvkm_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_memory_size (int /*<<< orphan*/ ) ; 
 int nvkm_vmm_get (struct nvkm_vmm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct nvkm_fault_buffer*) ; 

__attribute__((used)) static int
nvkm_fault_oneinit_buffer(struct nvkm_fault *fault, int id)
{
	struct nvkm_subdev *subdev = &fault->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_vmm *bar2 = nvkm_bar_bar2_vmm(device);
	struct nvkm_fault_buffer *buffer;
	int ret;

	if (!(buffer = kzalloc(sizeof(*buffer), GFP_KERNEL)))
		return -ENOMEM;
	buffer->fault = fault;
	buffer->id = id;
	buffer->entries = fault->func->buffer.entries(buffer);
	fault->buffer[id] = buffer;

	nvkm_debug(subdev, "buffer %d: %d entries\n", id, buffer->entries);

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, buffer->entries *
			      fault->func->buffer.entry_size, 0x1000, true,
			      &buffer->mem);
	if (ret)
		return ret;

	ret = nvkm_vmm_get(bar2, 12, nvkm_memory_size(buffer->mem),
			   &buffer->vma);
	if (ret)
		return ret;

	return nvkm_memory_map(buffer->mem, 0, bar2, buffer->vma, NULL, 0);
}