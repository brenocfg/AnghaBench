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
struct nvkm_gpuobj {int /*<<< orphan*/  memory; int /*<<< orphan*/ * func; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_gpuobj_heap ; 

__attribute__((used)) static void
nvkm_gpuobj_heap_release(struct nvkm_gpuobj *gpuobj)
{
	gpuobj->func = &nvkm_gpuobj_heap;
	nvkm_done(gpuobj->memory);
}