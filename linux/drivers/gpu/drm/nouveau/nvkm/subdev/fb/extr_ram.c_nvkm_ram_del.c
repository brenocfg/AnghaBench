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
struct nvkm_ram {int /*<<< orphan*/  vram; TYPE_1__* func; } ;
struct TYPE_2__ {struct nvkm_ram* (* dtor ) (struct nvkm_ram*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct nvkm_ram*) ; 
 int /*<<< orphan*/  nvkm_mm_fini (int /*<<< orphan*/ *) ; 
 struct nvkm_ram* stub1 (struct nvkm_ram*) ; 

void
nvkm_ram_del(struct nvkm_ram **pram)
{
	struct nvkm_ram *ram = *pram;
	if (ram && !WARN_ON(!ram->func)) {
		if (ram->func->dtor)
			*pram = ram->func->dtor(ram);
		nvkm_mm_fini(&ram->vram);
		kfree(*pram);
		*pram = NULL;
	}
}