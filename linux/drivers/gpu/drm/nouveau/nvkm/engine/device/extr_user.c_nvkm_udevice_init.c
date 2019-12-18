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
struct nvkm_udevice {struct nvkm_device* device; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvkm_device_init (struct nvkm_device*) ; 
 struct nvkm_udevice* nvkm_udevice (struct nvkm_object*) ; 

__attribute__((used)) static int
nvkm_udevice_init(struct nvkm_object *object)
{
	struct nvkm_udevice *udev = nvkm_udevice(object);
	struct nvkm_device *device = udev->device;
	int ret = 0;

	mutex_lock(&device->mutex);
	if (!device->refcount++) {
		ret = nvkm_device_init(device);
		if (ret) {
			device->refcount--;
			goto done;
		}
	}

done:
	mutex_unlock(&device->mutex);
	return ret;
}