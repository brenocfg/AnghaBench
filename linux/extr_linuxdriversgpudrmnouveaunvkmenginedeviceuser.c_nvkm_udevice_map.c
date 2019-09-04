#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_udevice {struct nvkm_device* device; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_device {TYPE_1__* func; } ;
typedef  enum nvkm_object_map { ____Placeholder_nvkm_object_map } nvkm_object_map ;
struct TYPE_2__ {int /*<<< orphan*/  (* resource_size ) (struct nvkm_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* resource_addr ) (struct nvkm_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int NVKM_OBJECT_MAP_IO ; 
 struct nvkm_udevice* nvkm_udevice (struct nvkm_object*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_udevice_map(struct nvkm_object *object, void *argv, u32 argc,
		 enum nvkm_object_map *type, u64 *addr, u64 *size)
{
	struct nvkm_udevice *udev = nvkm_udevice(object);
	struct nvkm_device *device = udev->device;
	*type = NVKM_OBJECT_MAP_IO;
	*addr = device->func->resource_addr(device, 0);
	*size = device->func->resource_size(device, 0);
	return 0;
}