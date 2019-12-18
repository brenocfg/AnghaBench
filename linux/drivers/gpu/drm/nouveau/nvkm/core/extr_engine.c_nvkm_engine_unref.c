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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct nvkm_engine {scalar_t__ usecount; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_subdev_fini (TYPE_1__*,int) ; 

void
nvkm_engine_unref(struct nvkm_engine **pengine)
{
	struct nvkm_engine *engine = *pengine;
	if (engine) {
		mutex_lock(&engine->subdev.mutex);
		if (--engine->usecount == 0)
			nvkm_subdev_fini(&engine->subdev, false);
		mutex_unlock(&engine->subdev.mutex);
		*pengine = NULL;
	}
}