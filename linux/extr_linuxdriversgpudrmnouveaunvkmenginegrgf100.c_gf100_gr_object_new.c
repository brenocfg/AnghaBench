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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * func; } ;
struct nvkm_oclass {TYPE_1__ base; int /*<<< orphan*/  parent; } ;
struct nvkm_object {int dummy; } ;
struct gf100_gr_object {struct gf100_gr_chan* chan; struct nvkm_object object; } ;
struct gf100_gr_chan {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gf100_gr_chan* gf100_gr_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf100_gr_object_func ; 
 struct gf100_gr_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,struct nvkm_object*) ; 

__attribute__((used)) static int
gf100_gr_object_new(const struct nvkm_oclass *oclass, void *data, u32 size,
		    struct nvkm_object **pobject)
{
	struct gf100_gr_chan *chan = gf100_gr_chan(oclass->parent);
	struct gf100_gr_object *object;

	if (!(object = kzalloc(sizeof(*object), GFP_KERNEL)))
		return -ENOMEM;
	*pobject = &object->object;

	nvkm_object_ctor(oclass->base.func ? oclass->base.func :
			 &gf100_gr_object_func, oclass, &object->object);
	object->chan = chan;
	return 0;
}