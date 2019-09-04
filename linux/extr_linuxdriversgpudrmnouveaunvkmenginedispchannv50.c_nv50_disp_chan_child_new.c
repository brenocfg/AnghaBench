#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_oclass {int /*<<< orphan*/  handle; struct nvkm_device_oclass* priv; int /*<<< orphan*/  parent; } ;
struct nvkm_object {int dummy; } ;
struct nvkm_device_oclass {int (* ctor ) (struct nvkm_device*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct nvkm_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  object; struct nvkm_object base; } ;
struct nv50_disp_chan_object {scalar_t__ hash; TYPE_5__ oproxy; struct nv50_disp* disp; } ;
struct nv50_disp_chan {TYPE_4__* func; struct nv50_disp* disp; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;
struct TYPE_8__ {TYPE_2__ engine; } ;
struct nv50_disp {TYPE_3__ base; } ;
struct TYPE_9__ {scalar_t__ (* bind ) (struct nv50_disp_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv50_disp_chan_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct nv50_disp_chan* nv50_disp_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_disp_chan_child_func_ ; 
 int /*<<< orphan*/  nvkm_oproxy_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,TYPE_5__*) ; 
 int stub1 (struct nvkm_device*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct nv50_disp_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv50_disp_chan_child_new(const struct nvkm_oclass *oclass,
			 void *argv, u32 argc, struct nvkm_object **pobject)
{
	struct nv50_disp_chan *chan = nv50_disp_chan(oclass->parent);
	struct nv50_disp *disp = chan->disp;
	struct nvkm_device *device = disp->base.engine.subdev.device;
	const struct nvkm_device_oclass *sclass = oclass->priv;
	struct nv50_disp_chan_object *object;
	int ret;

	if (!(object = kzalloc(sizeof(*object), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_oproxy_ctor(&nv50_disp_chan_child_func_, oclass, &object->oproxy);
	object->disp = disp;
	*pobject = &object->oproxy.base;

	ret = sclass->ctor(device, oclass, argv, argc, &object->oproxy.object);
	if (ret)
		return ret;

	object->hash = chan->func->bind(chan, object->oproxy.object,
					      oclass->handle);
	if (object->hash < 0)
		return object->hash;

	return 0;
}