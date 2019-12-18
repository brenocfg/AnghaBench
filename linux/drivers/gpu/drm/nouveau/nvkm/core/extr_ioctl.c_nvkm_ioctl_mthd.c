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
struct nvif_ioctl_mthd_v0 {int /*<<< orphan*/  method; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int /*<<< orphan*/ ,...) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_ioctl_mthd_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_object_mthd (struct nvkm_object*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_ioctl_mthd(struct nvkm_client *client,
		struct nvkm_object *object, void *data, u32 size)
{
	union {
		struct nvif_ioctl_mthd_v0 v0;
	} *args = data;
	int ret = -ENOSYS;

	nvif_ioctl(object, "mthd size %d\n", size);
	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, true))) {
		nvif_ioctl(object, "mthd vers %d mthd %02x\n",
			   args->v0.version, args->v0.method);
		ret = nvkm_object_mthd(object, args->v0.method, data, size);
	}

	return ret;
}