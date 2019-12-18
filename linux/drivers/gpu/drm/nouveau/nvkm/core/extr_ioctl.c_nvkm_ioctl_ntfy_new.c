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
struct nvkm_event {int dummy; } ;
struct nvkm_client {int dummy; } ;
struct nvif_ioctl_ntfy_new_v0 {int index; int /*<<< orphan*/  event; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int /*<<< orphan*/ ,...) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nvif_ioctl_ntfy_new_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvkm_client_notify_new (struct nvkm_object*,struct nvkm_event*,void*,int /*<<< orphan*/ ) ; 
 int nvkm_object_ntfy (struct nvkm_object*,int /*<<< orphan*/ ,struct nvkm_event**) ; 

__attribute__((used)) static int
nvkm_ioctl_ntfy_new(struct nvkm_client *client,
		    struct nvkm_object *object, void *data, u32 size)
{
	union {
		struct nvif_ioctl_ntfy_new_v0 v0;
	} *args = data;
	struct nvkm_event *event;
	int ret = -ENOSYS;

	nvif_ioctl(object, "ntfy new size %d\n", size);
	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, true))) {
		nvif_ioctl(object, "ntfy new vers %d event %02x\n",
			   args->v0.version, args->v0.event);
		ret = nvkm_object_ntfy(object, args->v0.event, &event);
		if (ret == 0) {
			ret = nvkm_client_notify_new(object, event, data, size);
			if (ret >= 0) {
				args->v0.index = ret;
				ret = 0;
			}
		}
	}

	return ret;
}