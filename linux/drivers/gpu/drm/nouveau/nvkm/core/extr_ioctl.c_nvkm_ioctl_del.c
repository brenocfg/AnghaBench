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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_object {int dummy; } ;
struct nvkm_client {int dummy; } ;
struct nvif_ioctl_del {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,...) ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct nvif_ioctl_del) ; 
 int /*<<< orphan*/  nvkm_object_del (struct nvkm_object**) ; 
 int /*<<< orphan*/  nvkm_object_fini (struct nvkm_object*,int) ; 

__attribute__((used)) static int
nvkm_ioctl_del(struct nvkm_client *client,
	       struct nvkm_object *object, void *data, u32 size)
{
	union {
		struct nvif_ioctl_del none;
	} *args = data;
	int ret = -ENOSYS;

	nvif_ioctl(object, "delete size %d\n", size);
	if (!(ret = nvif_unvers(ret, &data, &size, args->none))) {
		nvif_ioctl(object, "delete\n");
		nvkm_object_fini(object, false);
		nvkm_object_del(&object);
	}

	return ret ? ret : 1;
}