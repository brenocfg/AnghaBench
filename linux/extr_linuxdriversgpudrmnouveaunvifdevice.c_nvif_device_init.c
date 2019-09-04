#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvif_object {int dummy; } ;
struct TYPE_4__ {scalar_t__ version; } ;
struct TYPE_3__ {int /*<<< orphan*/ * func; } ;
struct nvif_device {TYPE_2__ info; int /*<<< orphan*/  object; TYPE_1__ user; int /*<<< orphan*/ * runlist; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  NV_DEVICE_V0_INFO ; 
 int nvif_object_init (struct nvif_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nvif_object_mthd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

int
nvif_device_init(struct nvif_object *parent, u32 handle, s32 oclass,
		 void *data, u32 size, struct nvif_device *device)
{
	int ret = nvif_object_init(parent, handle, oclass, data, size,
				   &device->object);
	device->runlist = NULL;
	device->user.func = NULL;
	if (ret == 0) {
		device->info.version = 0;
		ret = nvif_object_mthd(&device->object, NV_DEVICE_V0_INFO,
				       &device->info, sizeof(device->info));
	}
	return ret;
}