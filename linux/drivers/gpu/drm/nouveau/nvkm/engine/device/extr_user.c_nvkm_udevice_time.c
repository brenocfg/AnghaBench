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
struct nvkm_udevice {struct nvkm_device* device; struct nvkm_object object; } ;
struct nvkm_device {int /*<<< orphan*/  timer; } ;
struct nv_device_time_v0 {int /*<<< orphan*/  time; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  nvif_ioctl (struct nvkm_object*,char*,int /*<<< orphan*/ ) ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct nv_device_time_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_timer_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_udevice_time(struct nvkm_udevice *udev, void *data, u32 size)
{
	struct nvkm_object *object = &udev->object;
	struct nvkm_device *device = udev->device;
	union {
		struct nv_device_time_v0 v0;
	} *args = data;
	int ret = -ENOSYS;

	nvif_ioctl(object, "device time size %d\n", size);
	if (!(ret = nvif_unpack(ret, &data, &size, args->v0, 0, 0, false))) {
		nvif_ioctl(object, "device time vers %d\n", args->v0.version);
		args->v0.time = nvkm_timer_read(device->timer);
	}

	return ret;
}