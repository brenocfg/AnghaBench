#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvkm_subdev {int /*<<< orphan*/  device; } ;
struct TYPE_10__ {TYPE_4__* device; } ;
struct nvkm_mmu {int /*<<< orphan*/  vmm; TYPE_2__* func; TYPE_5__ subdev; } ;
struct TYPE_9__ {TYPE_3__* fb; } ;
struct TYPE_8__ {scalar_t__ ram; } ;
struct TYPE_6__ {scalar_t__ global; } ;
struct TYPE_7__ {TYPE_1__ vmm; } ;

/* Variables and functions */
 struct nvkm_mmu* nvkm_mmu (struct nvkm_subdev*) ; 
 int /*<<< orphan*/  nvkm_mmu_host (struct nvkm_mmu*) ; 
 int /*<<< orphan*/  nvkm_mmu_vram (struct nvkm_mmu*) ; 
 int nvkm_vmm_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvkm_mmu_oneinit(struct nvkm_subdev *subdev)
{
	struct nvkm_mmu *mmu = nvkm_mmu(subdev);

	/* Determine available memory types. */
	if (mmu->subdev.device->fb && mmu->subdev.device->fb->ram)
		nvkm_mmu_vram(mmu);
	else
		nvkm_mmu_host(mmu);

	if (mmu->func->vmm.global) {
		int ret = nvkm_vmm_new(subdev->device, 0, 0, NULL, 0, NULL,
				       "gart", &mmu->vmm);
		if (ret)
			return ret;
	}

	return 0;
}