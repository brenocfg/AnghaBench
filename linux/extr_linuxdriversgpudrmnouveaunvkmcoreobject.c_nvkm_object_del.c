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
struct nvkm_object {int /*<<< orphan*/  head; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct nvkm_object*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nvkm_object* nvkm_object_dtor (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_object_remove (struct nvkm_object*) ; 

void
nvkm_object_del(struct nvkm_object **pobject)
{
	struct nvkm_object *object = *pobject;
	if (object && !WARN_ON(!object->func)) {
		*pobject = nvkm_object_dtor(object);
		nvkm_object_remove(object);
		list_del(&object->head);
		kfree(*pobject);
		*pobject = NULL;
	}
}