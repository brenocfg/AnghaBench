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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {void* ptr; scalar_t__ size; } ;
struct nvif_object {TYPE_2__ map; struct nvif_client* client; } ;
struct nvif_client {TYPE_1__* driver; } ;
struct TYPE_3__ {void* (* map ) (struct nvif_client*,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int nvif_object_map_handle (struct nvif_object*,void*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  nvif_object_unmap_handle (struct nvif_object*) ; 
 void* stub1 (struct nvif_client*,scalar_t__,scalar_t__) ; 

int
nvif_object_map(struct nvif_object *object, void *argv, u32 argc)
{
	struct nvif_client *client = object->client;
	u64 handle, length;
	int ret = nvif_object_map_handle(object, argv, argc, &handle, &length);
	if (ret >= 0) {
		if (ret) {
			object->map.ptr = client->driver->map(client,
							      handle,
							      length);
			if (ret = -ENOMEM, object->map.ptr) {
				object->map.size = length;
				return 0;
			}
		} else {
			object->map.ptr = (void *)(unsigned long)handle;
			return 0;
		}
		nvif_object_unmap_handle(object);
	}
	return ret;
}