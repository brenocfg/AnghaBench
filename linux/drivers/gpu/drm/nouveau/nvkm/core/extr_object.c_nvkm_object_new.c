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
struct TYPE_2__ {struct nvkm_object_func* func; } ;
struct nvkm_oclass {TYPE_1__ base; } ;
struct nvkm_object_func {int dummy; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 struct nvkm_object_func nvkm_object_func ; 
 int nvkm_object_new_ (struct nvkm_object_func const*,struct nvkm_oclass const*,void*,int /*<<< orphan*/ ,struct nvkm_object**) ; 

int
nvkm_object_new(const struct nvkm_oclass *oclass, void *data, u32 size,
		struct nvkm_object **pobject)
{
	const struct nvkm_object_func *func =
		oclass->base.func ? oclass->base.func : &nvkm_object_func;
	return nvkm_object_new_(func, oclass, data, size, pobject);
}