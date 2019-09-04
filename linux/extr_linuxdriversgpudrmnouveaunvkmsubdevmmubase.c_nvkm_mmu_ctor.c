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
struct TYPE_3__ {int /*<<< orphan*/  user; } ;
struct nvkm_mmu_func {TYPE_1__ mmu; int /*<<< orphan*/  dma_bits; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; int /*<<< orphan*/  ctor; } ;
struct nvkm_mmu {TYPE_2__ user; int /*<<< orphan*/  dma_bits; struct nvkm_mmu_func const* func; int /*<<< orphan*/  subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_mmu ; 
 int /*<<< orphan*/  nvkm_mmu_ptc_init (struct nvkm_mmu*) ; 
 int /*<<< orphan*/  nvkm_subdev_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_ummu_new ; 

void
nvkm_mmu_ctor(const struct nvkm_mmu_func *func, struct nvkm_device *device,
	      int index, struct nvkm_mmu *mmu)
{
	nvkm_subdev_ctor(&nvkm_mmu, device, index, &mmu->subdev);
	mmu->func = func;
	mmu->dma_bits = func->dma_bits;
	nvkm_mmu_ptc_init(mmu);
	mmu->user.ctor = nvkm_ummu_new;
	mmu->user.base = func->mmu.user;
}