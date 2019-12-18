#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_iter {int /*<<< orphan*/  vmm; TYPE_2__** pt; struct nvkm_vmm_desc* desc; } ;
struct nvkm_vmm_desc {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__** pt; } ;
struct TYPE_3__ {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPT ; 
 int /*<<< orphan*/  nvkm_memory_boot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nvkm_vmm_boot_ptes(struct nvkm_vmm_iter *it, bool pfn, u32 ptei, u32 ptes)
{
	const struct nvkm_vmm_desc *desc = it->desc;
	const int type = desc->type == SPT;
	nvkm_memory_boot(it->pt[0]->pt[type]->memory, it->vmm);
	return false;
}