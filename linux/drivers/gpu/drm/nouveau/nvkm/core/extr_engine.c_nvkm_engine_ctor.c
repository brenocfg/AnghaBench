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
struct nvkm_engine_func {int dummy; } ;
struct nvkm_engine {int /*<<< orphan*/  lock; int /*<<< orphan*/  subdev; struct nvkm_engine_func const* func; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  nvkm_boolopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvkm_engine_func ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvkm_subdev_name ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nvkm_engine_ctor(const struct nvkm_engine_func *func,
		 struct nvkm_device *device, int index, bool enable,
		 struct nvkm_engine *engine)
{
	nvkm_subdev_ctor(&nvkm_engine_func, device, index, &engine->subdev);
	engine->func = func;

	if (!nvkm_boolopt(device->cfgopt, nvkm_subdev_name[index], enable)) {
		nvkm_debug(&engine->subdev, "disabled\n");
		return -ENODEV;
	}

	spin_lock_init(&engine->lock);
	return 0;
}