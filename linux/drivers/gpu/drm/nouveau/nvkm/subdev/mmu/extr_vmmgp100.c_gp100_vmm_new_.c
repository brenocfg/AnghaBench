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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_func {int dummy; } ;
struct nvkm_vmm {int replay; } ;
struct nvkm_mmu {int dummy; } ;
struct lock_class_key {int dummy; } ;
struct gp100_vmm_vn {int dummy; } ;
struct gp100_vmm_v0 {scalar_t__ fault_replay; } ;

/* Variables and functions */
 int ENOSYS ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct gp100_vmm_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct gp100_vmm_vn) ; 
 int nvkm_vmm_new_ (struct nvkm_vmm_func const*,struct nvkm_mmu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lock_class_key*,char const*,struct nvkm_vmm**) ; 

int
gp100_vmm_new_(const struct nvkm_vmm_func *func,
	       struct nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	       void *argv, u32 argc, struct lock_class_key *key,
	       const char *name, struct nvkm_vmm **pvmm)
{
	union {
		struct gp100_vmm_vn vn;
		struct gp100_vmm_v0 v0;
	} *args = argv;
	int ret = -ENOSYS;
	bool replay;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		replay = args->v0.fault_replay != 0;
	} else
	if (!(ret = nvif_unvers(ret, &argv, &argc, args->vn))) {
		replay = false;
	} else
		return ret;

	ret = nvkm_vmm_new_(func, mmu, 0, managed, addr, size, key, name, pvmm);
	if (ret)
		return ret;

	(*pvmm)->replay = replay;
	return 0;
}