#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct nvkm_udevice {struct nvkm_device* device; } ;
struct nvkm_oclass {struct nvkm_device_oclass const* priv; int /*<<< orphan*/  ctor; int /*<<< orphan*/  base; struct nvkm_engine* engine; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_engine {TYPE_2__* func; } ;
struct nvkm_device_oclass {int /*<<< orphan*/  base; } ;
struct nvkm_device {TYPE_4__* fault; TYPE_3__* mmu; } ;
struct TYPE_8__ {struct nvkm_device_oclass user; } ;
struct TYPE_7__ {struct nvkm_device_oclass user; } ;
struct TYPE_5__ {scalar_t__ (* sclass ) (struct nvkm_oclass*,int,struct nvkm_device_oclass const**) ;} ;
struct TYPE_6__ {TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long long NVKM_ENGINE_DISP ; 
 unsigned long long NVKM_ENGINE_DMAOBJ ; 
 unsigned long long NVKM_ENGINE_FIFO ; 
 unsigned long long NVKM_ENGINE_PM ; 
 int __ffs64 (unsigned long long) ; 
 struct nvkm_device_oclass nvkm_control_oclass ; 
 struct nvkm_engine* nvkm_device_engine (struct nvkm_device*,int) ; 
 struct nvkm_udevice* nvkm_udevice (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_udevice_child_new ; 
 scalar_t__ stub1 (struct nvkm_oclass*,int,struct nvkm_device_oclass const**) ; 

__attribute__((used)) static int
nvkm_udevice_child_get(struct nvkm_object *object, int index,
		       struct nvkm_oclass *oclass)
{
	struct nvkm_udevice *udev = nvkm_udevice(object);
	struct nvkm_device *device = udev->device;
	struct nvkm_engine *engine;
	u64 mask = (1ULL << NVKM_ENGINE_DMAOBJ) |
		   (1ULL << NVKM_ENGINE_FIFO) |
		   (1ULL << NVKM_ENGINE_DISP) |
		   (1ULL << NVKM_ENGINE_PM);
	const struct nvkm_device_oclass *sclass = NULL;
	int i;

	for (; i = __ffs64(mask), mask && !sclass; mask &= ~(1ULL << i)) {
		if (!(engine = nvkm_device_engine(device, i)) ||
		    !(engine->func->base.sclass))
			continue;
		oclass->engine = engine;

		index -= engine->func->base.sclass(oclass, index, &sclass);
	}

	if (!sclass) {
		if (index-- == 0)
			sclass = &nvkm_control_oclass;
		else if (device->mmu && index-- == 0)
			sclass = &device->mmu->user;
		else if (device->fault && index-- == 0)
			sclass = &device->fault->user;
		else
			return -EINVAL;

		oclass->base = sclass->base;
	}

	oclass->ctor = nvkm_udevice_child_new;
	oclass->priv = sclass;
	return 0;
}