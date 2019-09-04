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
struct TYPE_2__ {int (* unmap ) (struct nvkm_object*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ likely (int (*) (struct nvkm_object*)) ; 
 int stub1 (struct nvkm_object*) ; 

int
nvkm_object_unmap(struct nvkm_object *object)
{
	if (likely(object->func->unmap))
		return object->func->unmap(object);
	return -ENODEV;
}