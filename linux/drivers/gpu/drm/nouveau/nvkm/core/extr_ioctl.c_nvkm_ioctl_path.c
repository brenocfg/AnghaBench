#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct nvkm_object {scalar_t__ route; int /*<<< orphan*/  token; } ;
struct nvkm_client {int /*<<< orphan*/  object; } ;
struct TYPE_3__ {scalar_t__ version; int (* func ) (struct nvkm_client*,struct nvkm_object*,void*,size_t) ;} ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EACCES ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct nvkm_object*) ; 
 scalar_t__ NVIF_IOCTL_V0_OWNER_ANY ; 
 int PTR_ERR (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvif_ioctl (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* nvkm_ioctl_v0 ; 
 struct nvkm_object* nvkm_object_search (struct nvkm_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct nvkm_client*,struct nvkm_object*,void*,size_t) ; 

__attribute__((used)) static int
nvkm_ioctl_path(struct nvkm_client *client, u64 handle, u32 type,
		void *data, u32 size, u8 owner, u8 *route, u64 *token)
{
	struct nvkm_object *object;
	int ret;

	object = nvkm_object_search(client, handle, NULL);
	if (IS_ERR(object)) {
		nvif_ioctl(&client->object, "object not found\n");
		return PTR_ERR(object);
	}

	if (owner != NVIF_IOCTL_V0_OWNER_ANY && owner != object->route) {
		nvif_ioctl(&client->object, "route != owner\n");
		return -EACCES;
	}
	*route = object->route;
	*token = object->token;

	if (ret = -EINVAL, type < ARRAY_SIZE(nvkm_ioctl_v0)) {
		if (nvkm_ioctl_v0[type].version == 0)
			ret = nvkm_ioctl_v0[type].func(client, object, data, size);
	}

	return ret;
}