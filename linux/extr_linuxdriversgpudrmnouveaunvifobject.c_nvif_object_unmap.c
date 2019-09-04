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
struct TYPE_4__ {int /*<<< orphan*/ * ptr; scalar_t__ size; } ;
struct nvif_object {TYPE_2__ map; struct nvif_client* client; } ;
struct nvif_client {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unmap ) (struct nvif_client*,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_object_unmap_handle (struct nvif_object*) ; 
 int /*<<< orphan*/  stub1 (struct nvif_client*,int /*<<< orphan*/ *,scalar_t__) ; 

void
nvif_object_unmap(struct nvif_object *object)
{
	struct nvif_client *client = object->client;
	if (object->map.ptr) {
		if (object->map.size) {
			client->driver->unmap(client, object->map.ptr,
						      object->map.size);
			object->map.size = 0;
		}
		object->map.ptr = NULL;
		nvif_object_unmap_handle(object);
	}
}