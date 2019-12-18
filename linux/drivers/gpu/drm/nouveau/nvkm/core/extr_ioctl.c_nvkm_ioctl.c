#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_client {int super; int /*<<< orphan*/ * data; struct nvkm_object object; } ;
struct nvif_ioctl_v0 {int /*<<< orphan*/  token; int /*<<< orphan*/  route; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/  object; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int,...) ; 
 int nvif_unpack (int,void**,int*,struct nvif_ioctl_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_ioctl_path (struct nvkm_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nvkm_ioctl(struct nvkm_client *client, bool supervisor,
	   void *data, u32 size, void **hack)
{
	struct nvkm_object *object = &client->object;
	union {
		struct nvif_ioctl_v0 v0;
	} *args = data;
	int ret = -ENOSYS;

	client->super = supervisor;
	nvif_ioctl(object, "size %d\n", size);

	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, true))) {
		nvif_ioctl(object,
			   "vers %d type %02x object %016llx owner %02x\n",
			   args->v0.version, args->v0.type, args->v0.object,
			   args->v0.owner);
		ret = nvkm_ioctl_path(client, args->v0.object, args->v0.type,
				      data, size, args->v0.owner,
				      &args->v0.route, &args->v0.token);
	}

	if (ret != 1) {
		nvif_ioctl(object, "return %d\n", ret);
		if (hack) {
			*hack = client->data;
			client->data = NULL;
		}
	}

	return ret;
}