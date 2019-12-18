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
struct nvkm_engine {int usecount; TYPE_1__ subdev; } ;

/* Variables and functions */
 struct nvkm_engine* ERR_PTR (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nvkm_subdev_init (TYPE_1__*) ; 

struct nvkm_engine *
nvkm_engine_ref(struct nvkm_engine *engine)
{
	if (engine) {
		mutex_lock(&engine->subdev.mutex);
		if (++engine->usecount == 1) {
			int ret = nvkm_subdev_init(&engine->subdev);
			if (ret) {
				engine->usecount--;
				mutex_unlock(&engine->subdev.mutex);
				return ERR_PTR(ret);
			}
		}
		mutex_unlock(&engine->subdev.mutex);
	}
	return engine;
}