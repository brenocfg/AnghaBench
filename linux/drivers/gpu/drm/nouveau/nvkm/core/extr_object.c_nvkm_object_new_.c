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
typedef  scalar_t__ u32 ;
struct nvkm_oclass {int dummy; } ;
struct nvkm_object_func {int dummy; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_object_ctor (struct nvkm_object_func const*,struct nvkm_oclass const*,struct nvkm_object*) ; 

int
nvkm_object_new_(const struct nvkm_object_func *func,
		 const struct nvkm_oclass *oclass, void *data, u32 size,
		 struct nvkm_object **pobject)
{
	if (size == 0) {
		if (!(*pobject = kzalloc(sizeof(**pobject), GFP_KERNEL)))
			return -ENOMEM;
		nvkm_object_ctor(func, oclass, *pobject);
		return 0;
	}
	return -ENOSYS;
}