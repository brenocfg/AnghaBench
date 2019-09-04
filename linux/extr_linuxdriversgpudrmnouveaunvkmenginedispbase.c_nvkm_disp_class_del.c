#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  engine; } ;
struct nvkm_oproxy {TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {TYPE_2__ subdev; } ;
struct nvkm_disp {TYPE_3__ engine; struct nvkm_oproxy* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nvkm_disp* nvkm_disp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvkm_disp_class_del(struct nvkm_oproxy *oproxy)
{
	struct nvkm_disp *disp = nvkm_disp(oproxy->base.engine);
	mutex_lock(&disp->engine.subdev.mutex);
	if (disp->client == oproxy)
		disp->client = NULL;
	mutex_unlock(&disp->engine.subdev.mutex);
}