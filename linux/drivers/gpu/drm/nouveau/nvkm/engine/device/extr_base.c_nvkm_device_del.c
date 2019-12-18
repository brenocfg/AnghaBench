#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {int dummy; } ;
struct nvkm_device {TYPE_1__* func; int /*<<< orphan*/  head; scalar_t__ pri; int /*<<< orphan*/  event; scalar_t__ disable_mask; } ;
struct TYPE_2__ {struct nvkm_device* (* dtor ) (struct nvkm_device*) ;} ;

/* Variables and functions */
 int NVKM_SUBDEV_NR ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct nvkm_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_devices_mutex ; 
 struct nvkm_subdev* nvkm_device_subdev (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_event_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_subdev_del (struct nvkm_subdev**) ; 
 struct nvkm_device* stub1 (struct nvkm_device*) ; 

void
nvkm_device_del(struct nvkm_device **pdevice)
{
	struct nvkm_device *device = *pdevice;
	int i;
	if (device) {
		mutex_lock(&nv_devices_mutex);
		device->disable_mask = 0;
		for (i = NVKM_SUBDEV_NR - 1; i >= 0; i--) {
			struct nvkm_subdev *subdev =
				nvkm_device_subdev(device, i);
			nvkm_subdev_del(&subdev);
		}

		nvkm_event_fini(&device->event);

		if (device->pri)
			iounmap(device->pri);
		list_del(&device->head);

		if (device->func->dtor)
			*pdevice = device->func->dtor(device);
		mutex_unlock(&nv_devices_mutex);

		kfree(*pdevice);
		*pdevice = NULL;
	}
}