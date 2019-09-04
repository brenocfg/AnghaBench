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
typedef  void u8 ;
struct nvkm_gpuobj {void* map; int /*<<< orphan*/ * func; TYPE_1__* node; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int offset; } ;

/* Variables and functions */
 scalar_t__ likely (void*) ; 
 int /*<<< orphan*/  nvkm_gpuobj_fast ; 
 int /*<<< orphan*/  nvkm_gpuobj_slow ; 
 void* nvkm_kmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
nvkm_gpuobj_acquire(struct nvkm_gpuobj *gpuobj)
{
	gpuobj->map = nvkm_kmap(gpuobj->parent);
	if (likely(gpuobj->map)) {
		gpuobj->map  = (u8 *)gpuobj->map + gpuobj->node->offset;
		gpuobj->func = &nvkm_gpuobj_fast;
	} else {
		gpuobj->func = &nvkm_gpuobj_slow;
	}
	return gpuobj->map;
}