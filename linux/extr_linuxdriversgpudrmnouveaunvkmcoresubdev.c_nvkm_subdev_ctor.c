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
struct nvkm_subdev_func {int dummy; } ;
struct nvkm_subdev {int index; int /*<<< orphan*/  debug; int /*<<< orphan*/  mutex; struct nvkm_device* device; struct nvkm_subdev_func const* func; } ;
struct nvkm_device {int /*<<< orphan*/  dbgopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mutex_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_dbgopt (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * nvkm_subdev_lock_class ; 
 char** nvkm_subdev_name ; 

void
nvkm_subdev_ctor(const struct nvkm_subdev_func *func,
		 struct nvkm_device *device, int index,
		 struct nvkm_subdev *subdev)
{
	const char *name = nvkm_subdev_name[index];
	subdev->func = func;
	subdev->device = device;
	subdev->index = index;

	__mutex_init(&subdev->mutex, name, &nvkm_subdev_lock_class[index]);
	subdev->debug = nvkm_dbgopt(device->dbgopt, name);
}