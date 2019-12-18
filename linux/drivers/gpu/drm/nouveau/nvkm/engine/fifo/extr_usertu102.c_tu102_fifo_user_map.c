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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {TYPE_2__* engine; } ;
struct nvkm_device {TYPE_3__* func; } ;
typedef  enum nvkm_object_map { ____Placeholder_nvkm_object_map } nvkm_object_map ;
struct TYPE_6__ {int (* resource_addr ) (struct nvkm_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int NVKM_OBJECT_MAP_IO ; 
 int stub1 (struct nvkm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tu102_fifo_user_map(struct nvkm_object *object, void *argv, u32 argc,
		    enum nvkm_object_map *type, u64 *addr, u64 *size)
{
	struct nvkm_device *device = object->engine->subdev.device;
	*addr = 0xbb0000 + device->func->resource_addr(device, 0);
	*size = 0x010000;
	*type = NVKM_OBJECT_MAP_IO;
	return 0;
}