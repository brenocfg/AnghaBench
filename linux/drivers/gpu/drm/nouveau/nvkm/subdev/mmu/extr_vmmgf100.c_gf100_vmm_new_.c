#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_func {int dummy; } ;
struct nvkm_vmm {int dummy; } ;
struct TYPE_6__ {TYPE_2__* device; } ;
struct nvkm_mmu {TYPE_3__ subdev; } ;
struct lock_class_key {int dummy; } ;
struct TYPE_5__ {TYPE_1__* fb; } ;
struct TYPE_4__ {int page; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int nv04_vmm_new_ (struct nvkm_vmm_func const*,struct nvkm_mmu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct lock_class_key*,char const*,struct nvkm_vmm**) ; 

int
gf100_vmm_new_(const struct nvkm_vmm_func *func_16,
	       const struct nvkm_vmm_func *func_17,
	       struct nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	       void *argv, u32 argc, struct lock_class_key *key,
	       const char *name, struct nvkm_vmm **pvmm)
{
	switch (mmu->subdev.device->fb->page) {
	case 16: return nv04_vmm_new_(func_16, mmu, 0, managed, addr, size,
				      argv, argc, key, name, pvmm);
	case 17: return nv04_vmm_new_(func_17, mmu, 0, managed, addr, size,
				      argv, argc, key, name, pvmm);
	default:
		WARN_ON(1);
		return -EINVAL;
	}
}