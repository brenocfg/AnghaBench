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
struct nvkm_oproxy {TYPE_2__* object; } ;
struct nvkm_oclass {TYPE_2__* parent; } ;
struct nvkm_object {int dummy; } ;
struct TYPE_4__ {TYPE_1__* func; } ;
struct TYPE_3__ {int (* sclass ) (TYPE_2__*,int,struct nvkm_oclass*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 struct nvkm_oproxy* nvkm_oproxy (struct nvkm_object*) ; 
 int stub1 (TYPE_2__*,int,struct nvkm_oclass*) ; 

__attribute__((used)) static int
nvkm_oproxy_sclass(struct nvkm_object *object, int index,
		   struct nvkm_oclass *oclass)
{
	struct nvkm_oproxy *oproxy = nvkm_oproxy(object);
	oclass->parent = oproxy->object;
	if (!oproxy->object->func->sclass)
		return -ENODEV;
	return oproxy->object->func->sclass(oproxy->object, index, oclass);
}