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
struct nvif_ioctl_wr_v0 {int size; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int /*<<< orphan*/ ,...) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_ioctl_wr_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_object_wr08 (struct nvkm_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_object_wr16 (struct nvkm_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_object_wr32 (struct nvkm_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_ioctl_wr(struct nvkm_client *client,
	      struct nvkm_object *object, void *data, u32 size)
{
	union {
		struct nvif_ioctl_wr_v0 v0;
	} *args = data;
	int ret = -ENOSYS;

	nvif_ioctl(object, "wr size %d\n", size);
	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, false))) {
		nvif_ioctl(object,
			   "wr vers %d size %d addr %016llx data %08x\n",
			   args->v0.version, args->v0.size, args->v0.addr,
			   args->v0.data);
	} else
		return ret;

	switch (args->v0.size) {
	case 1: return nvkm_object_wr08(object, args->v0.addr, args->v0.data);
	case 2: return nvkm_object_wr16(object, args->v0.addr, args->v0.data);
	case 4: return nvkm_object_wr32(object, args->v0.addr, args->v0.data);
	default:
		break;
	}

	return -EINVAL;
}