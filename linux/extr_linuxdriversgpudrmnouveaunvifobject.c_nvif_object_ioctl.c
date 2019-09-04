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
typedef  int u32 ;
struct nvif_object {int /*<<< orphan*/  priv; struct nvif_client* client; } ;
struct nvif_ioctl_v0 {scalar_t__ version; int /*<<< orphan*/  owner; scalar_t__ object; } ;
struct nvif_client {int /*<<< orphan*/  super; struct nvif_object object; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* ioctl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,void**) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  NVIF_IOCTL_V0_OWNER_ANY ; 
 scalar_t__ nvif_handle (struct nvif_object*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,void**) ; 

int
nvif_object_ioctl(struct nvif_object *object, void *data, u32 size, void **hack)
{
	struct nvif_client *client = object->client;
	union {
		struct nvif_ioctl_v0 v0;
	} *args = data;

	if (size >= sizeof(*args) && args->v0.version == 0) {
		if (object != &client->object)
			args->v0.object = nvif_handle(object);
		else
			args->v0.object = 0;
		args->v0.owner = NVIF_IOCTL_V0_OWNER_ANY;
	} else
		return -ENOSYS;

	return client->driver->ioctl(client->object.priv, client->super,
				     data, size, hack);
}