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
struct nvif_mmu {int /*<<< orphan*/  object; int /*<<< orphan*/  heap; int /*<<< orphan*/  type; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_object_fini (int /*<<< orphan*/ *) ; 

void
nvif_mmu_fini(struct nvif_mmu *mmu)
{
	kfree(mmu->kind);
	kfree(mmu->type);
	kfree(mmu->heap);
	nvif_object_fini(&mmu->object);
}