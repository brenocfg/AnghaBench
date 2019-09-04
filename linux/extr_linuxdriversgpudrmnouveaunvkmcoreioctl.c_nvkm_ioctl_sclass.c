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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  maxver; int /*<<< orphan*/  minver; int /*<<< orphan*/  oclass; } ;
struct nvkm_oclass {TYPE_3__ base; struct nvkm_client* client; } ;
struct nvkm_object {TYPE_1__* func; } ;
struct nvkm_client {int dummy; } ;
struct nvif_ioctl_sclass_v0 {int count; TYPE_2__* oclass; int /*<<< orphan*/  version; } ;
struct TYPE_5__ {int /*<<< orphan*/  maxver; int /*<<< orphan*/  minver; int /*<<< orphan*/  oclass; } ;
struct TYPE_4__ {scalar_t__ (* sclass ) (struct nvkm_object*,int,struct nvkm_oclass*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int,...) ; 
 int nvif_unpack (int,void**,int*,struct nvif_ioctl_sclass_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct nvkm_object*,int,struct nvkm_oclass*) ; 

__attribute__((used)) static int
nvkm_ioctl_sclass(struct nvkm_client *client,
		  struct nvkm_object *object, void *data, u32 size)
{
	union {
		struct nvif_ioctl_sclass_v0 v0;
	} *args = data;
	struct nvkm_oclass oclass = { .client = client };
	int ret = -ENOSYS, i = 0;

	nvif_ioctl(object, "sclass size %d\n", size);
	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, true))) {
		nvif_ioctl(object, "sclass vers %d count %d\n",
			   args->v0.version, args->v0.count);
		if (size != args->v0.count * sizeof(args->v0.oclass[0]))
			return -EINVAL;

		while (object->func->sclass &&
		       object->func->sclass(object, i, &oclass) >= 0) {
			if (i < args->v0.count) {
				args->v0.oclass[i].oclass = oclass.base.oclass;
				args->v0.oclass[i].minver = oclass.base.minver;
				args->v0.oclass[i].maxver = oclass.base.maxver;
			}
			i++;
		}

		args->v0.count = i;
	}

	return ret;
}