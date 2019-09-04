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
struct nvkm_gpuobj {int /*<<< orphan*/  memory; int /*<<< orphan*/  heap; int /*<<< orphan*/  node; TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  heap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvkm_gpuobj*) ; 
 int /*<<< orphan*/  nvkm_memory_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mm_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_mm_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
nvkm_gpuobj_del(struct nvkm_gpuobj **pgpuobj)
{
	struct nvkm_gpuobj *gpuobj = *pgpuobj;
	if (gpuobj) {
		if (gpuobj->parent)
			nvkm_mm_free(&gpuobj->parent->heap, &gpuobj->node);
		nvkm_mm_fini(&gpuobj->heap);
		nvkm_memory_unref(&gpuobj->memory);
		kfree(*pgpuobj);
		*pgpuobj = NULL;
	}
}