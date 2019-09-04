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
struct nvkm_object {TYPE_1__* func; } ;
struct nvkm_gpuobj {int dummy; } ;
struct TYPE_2__ {int (* bind ) (struct nvkm_object*,struct nvkm_gpuobj*,int,struct nvkm_gpuobj**) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct nvkm_object*,struct nvkm_gpuobj*,int,struct nvkm_gpuobj**) ; 

int
nvkm_object_bind(struct nvkm_object *object, struct nvkm_gpuobj *gpuobj,
		 int align, struct nvkm_gpuobj **pgpuobj)
{
	if (object->func->bind)
		return object->func->bind(object, gpuobj, align, pgpuobj);
	return -ENODEV;
}