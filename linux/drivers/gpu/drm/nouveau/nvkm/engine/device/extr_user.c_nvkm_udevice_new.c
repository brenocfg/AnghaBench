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
struct nvkm_udevice {void* device; struct nvkm_object object; } ;
struct nvkm_oclass {struct nvkm_client* client; } ;
struct nvkm_object_func {int dummy; } ;
struct nvkm_client {int /*<<< orphan*/  device; scalar_t__ super; struct nvkm_object object; } ;
struct nv_device_v0 {int /*<<< orphan*/  device; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_udevice* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int /*<<< orphan*/ ,...) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nv_device_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* nvkm_device_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_object_ctor (struct nvkm_object_func const*,struct nvkm_oclass const*,struct nvkm_object*) ; 
 struct nvkm_object_func nvkm_udevice ; 
 struct nvkm_object_func nvkm_udevice_super ; 

__attribute__((used)) static int
nvkm_udevice_new(const struct nvkm_oclass *oclass, void *data, u32 size,
		 struct nvkm_object **pobject)
{
	union {
		struct nv_device_v0 v0;
	} *args = data;
	struct nvkm_client *client = oclass->client;
	struct nvkm_object *parent = &client->object;
	const struct nvkm_object_func *func;
	struct nvkm_udevice *udev;
	int ret = -ENOSYS;

	nvif_ioctl(parent, "create device size %d\n", size);
	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, false))) {
		nvif_ioctl(parent, "create device v%d device %016llx\n",
			   args->v0.version, args->v0.device);
	} else
		return ret;

	/* give priviledged clients register access */
	if (client->super)
		func = &nvkm_udevice_super;
	else
		func = &nvkm_udevice;

	if (!(udev = kzalloc(sizeof(*udev), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_object_ctor(func, oclass, &udev->object);
	*pobject = &udev->object;

	/* find the device that matches what the client requested */
	if (args->v0.device != ~0)
		udev->device = nvkm_device_find(args->v0.device);
	else
		udev->device = nvkm_device_find(client->device);
	if (!udev->device)
		return -ENODEV;

	return 0;
}