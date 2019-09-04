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
struct nvkm_gpuobj {void* map; int /*<<< orphan*/ * func; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 scalar_t__ likely (void*) ; 
 int /*<<< orphan*/  nvkm_gpuobj_heap_fast ; 
 int /*<<< orphan*/  nvkm_gpuobj_heap_slow ; 
 void* nvkm_kmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
nvkm_gpuobj_heap_acquire(struct nvkm_gpuobj *gpuobj)
{
	gpuobj->map = nvkm_kmap(gpuobj->memory);
	if (likely(gpuobj->map))
		gpuobj->func = &nvkm_gpuobj_heap_fast;
	else
		gpuobj->func = &nvkm_gpuobj_heap_slow;
	return gpuobj->map;
}