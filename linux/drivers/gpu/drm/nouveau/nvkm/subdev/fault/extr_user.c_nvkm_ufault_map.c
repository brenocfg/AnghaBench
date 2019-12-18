#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_fault_buffer {int /*<<< orphan*/  mem; scalar_t__ addr; TYPE_2__* fault; } ;
struct nvkm_device {TYPE_3__* func; } ;
typedef  enum nvkm_object_map { ____Placeholder_nvkm_object_map } nvkm_object_map ;
struct TYPE_6__ {scalar_t__ (* resource_addr ) (struct nvkm_device*,int) ;} ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int NVKM_OBJECT_MAP_IO ; 
 struct nvkm_fault_buffer* nvkm_fault_buffer (struct nvkm_object*) ; 
 scalar_t__ nvkm_memory_size (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct nvkm_device*,int) ; 

__attribute__((used)) static int
nvkm_ufault_map(struct nvkm_object *object, void *argv, u32 argc,
		enum nvkm_object_map *type, u64 *addr, u64 *size)
{
	struct nvkm_fault_buffer *buffer = nvkm_fault_buffer(object);
	struct nvkm_device *device = buffer->fault->subdev.device;
	*type = NVKM_OBJECT_MAP_IO;
	*addr = device->func->resource_addr(device, 3) + buffer->addr;
	*size = nvkm_memory_size(buffer->mem);
	return 0;
}