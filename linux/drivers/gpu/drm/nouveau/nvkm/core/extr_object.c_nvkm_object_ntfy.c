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
struct nvkm_object {TYPE_1__* func; } ;
struct nvkm_event {int dummy; } ;
struct TYPE_2__ {int (* ntfy ) (struct nvkm_object*,int /*<<< orphan*/ ,struct nvkm_event**) ;} ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ likely (int (*) (struct nvkm_object*,int /*<<< orphan*/ ,struct nvkm_event**)) ; 
 int stub1 (struct nvkm_object*,int /*<<< orphan*/ ,struct nvkm_event**) ; 

int
nvkm_object_ntfy(struct nvkm_object *object, u32 mthd,
		 struct nvkm_event **pevent)
{
	if (likely(object->func->ntfy))
		return object->func->ntfy(object, mthd, pevent);
	return -ENODEV;
}