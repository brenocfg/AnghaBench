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
struct nvkm_object {int dummy; } ;
struct nvkm_oproxy {int /*<<< orphan*/  object; struct nvkm_object base; } ;
struct nvkm_oclass {int /*<<< orphan*/  engine; struct nvkm_disp_oclass* engn; } ;
struct nvkm_disp_oclass {int (* ctor ) (struct nvkm_disp*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nvkm_disp {TYPE_2__ engine; struct nvkm_oproxy* client; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nvkm_disp* nvkm_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_disp_class ; 
 int nvkm_oproxy_new_ (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_oproxy**) ; 
 int stub1 (struct nvkm_disp*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvkm_disp_class_new(struct nvkm_device *device,
		    const struct nvkm_oclass *oclass, void *data, u32 size,
		    struct nvkm_object **pobject)
{
	const struct nvkm_disp_oclass *sclass = oclass->engn;
	struct nvkm_disp *disp = nvkm_disp(oclass->engine);
	struct nvkm_oproxy *oproxy;
	int ret;

	ret = nvkm_oproxy_new_(&nvkm_disp_class, oclass, &oproxy);
	if (ret)
		return ret;
	*pobject = &oproxy->base;

	mutex_lock(&disp->engine.subdev.mutex);
	if (disp->client) {
		mutex_unlock(&disp->engine.subdev.mutex);
		return -EBUSY;
	}
	disp->client = oproxy;
	mutex_unlock(&disp->engine.subdev.mutex);

	return sclass->ctor(disp, oclass, data, size, &oproxy->object);
}